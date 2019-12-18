#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct isc_ctrls {size_t* hist_count; size_t** hist_minmax; size_t* offset; size_t* gain; } ;

/* Variables and functions */
 int HIST_ENTRIES ; 
 size_t HIST_MAX_INDEX ; 
 size_t HIST_MIN_INDEX ; 
 size_t ISC_HIS_CFG_MODE_B ; 
 size_t ISC_HIS_CFG_MODE_GB ; 
 size_t ISC_HIS_CFG_MODE_GR ; 
 size_t ISC_WB_O_ZERO_VAL ; 
 size_t div_u64 (int,size_t) ; 

__attribute__((used)) static void isc_wb_update(struct isc_ctrls *ctrls)
{
	u32 *hist_count = &ctrls->hist_count[0];
	u32 c, offset[4];
	u64 avg = 0;
	/* We compute two gains, stretch gain and grey world gain */
	u32 s_gain[4], gw_gain[4];

	/*
	 * According to Grey World, we need to set gains for R/B to normalize
	 * them towards the green channel.
	 * Thus we want to keep Green as fixed and adjust only Red/Blue
	 * Compute the average of the both green channels first
	 */
	avg = (u64)hist_count[ISC_HIS_CFG_MODE_GR] +
		(u64)hist_count[ISC_HIS_CFG_MODE_GB];
	avg >>= 1;

	/* Green histogram is null, nothing to do */
	if (!avg)
		return;

	for (c = ISC_HIS_CFG_MODE_GR; c <= ISC_HIS_CFG_MODE_B; c++) {
		/*
		 * the color offset is the minimum value of the histogram.
		 * we stretch this color to the full range by substracting
		 * this value from the color component.
		 */
		offset[c] = ctrls->hist_minmax[c][HIST_MIN_INDEX];
		/*
		 * The offset is always at least 1. If the offset is 1, we do
		 * not need to adjust it, so our result must be zero.
		 * the offset is computed in a histogram on 9 bits (0..512)
		 * but the offset in register is based on
		 * 12 bits pipeline (0..4096).
		 * we need to shift with the 3 bits that the histogram is
		 * ignoring
		 */
		ctrls->offset[c] = (offset[c] - 1) << 3;

		/* the offset is then taken and converted to 2's complements */
		if (!ctrls->offset[c])
			ctrls->offset[c] = ISC_WB_O_ZERO_VAL;

		/*
		 * the stretch gain is the total number of histogram bins
		 * divided by the actual range of color component (Max - Min)
		 * If we compute gain like this, the actual color component
		 * will be stretched to the full histogram.
		 * We need to shift 9 bits for precision, we have 9 bits for
		 * decimals
		 */
		s_gain[c] = (HIST_ENTRIES << 9) /
			(ctrls->hist_minmax[c][HIST_MAX_INDEX] -
			ctrls->hist_minmax[c][HIST_MIN_INDEX] + 1);

		/*
		 * Now we have to compute the gain w.r.t. the average.
		 * Add/lose gain to the component towards the average.
		 * If it happens that the component is zero, use the
		 * fixed point value : 1.0 gain.
		 */
		if (hist_count[c])
			gw_gain[c] = div_u64(avg << 9, hist_count[c]);
		else
			gw_gain[c] = 1 << 9;

		/* multiply both gains and adjust for decimals */
		ctrls->gain[c] = s_gain[c] * gw_gain[c];
		ctrls->gain[c] >>= 9;
	}
}