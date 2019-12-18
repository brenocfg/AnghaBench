#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dispc_device {int /*<<< orphan*/  dss; TYPE_1__* feat; } ;
typedef  scalar_t__ (* dispc_div_calc_func ) (int,int,unsigned long,unsigned long,void*) ;
struct TYPE_2__ {unsigned long min_pcd; } ;

/* Variables and functions */
 unsigned int CONFIG_OMAP2_DSS_MIN_FCK_PER_PCK ; 
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  FEAT_CORE_CLK_DIV ; 
 unsigned long ULONG_MAX ; 
 unsigned long dispc_core_clk_rate (struct dispc_device*) ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 unsigned long dss_get_max_fck_rate (int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,unsigned long) ; 
 int min (unsigned long,unsigned long) ; 

bool dispc_div_calc(struct dispc_device *dispc, unsigned long dispc_freq,
		    unsigned long pck_min, unsigned long pck_max,
		    dispc_div_calc_func func, void *data)
{
	int lckd, lckd_start, lckd_stop;
	int pckd, pckd_start, pckd_stop;
	unsigned long pck, lck;
	unsigned long lck_max;
	unsigned long pckd_hw_min, pckd_hw_max;
	unsigned int min_fck_per_pck;
	unsigned long fck;

#ifdef CONFIG_OMAP2_DSS_MIN_FCK_PER_PCK
	min_fck_per_pck = CONFIG_OMAP2_DSS_MIN_FCK_PER_PCK;
#else
	min_fck_per_pck = 0;
#endif

	pckd_hw_min = dispc->feat->min_pcd;
	pckd_hw_max = 255;

	lck_max = dss_get_max_fck_rate(dispc->dss);

	pck_min = pck_min ? pck_min : 1;
	pck_max = pck_max ? pck_max : ULONG_MAX;

	lckd_start = max(DIV_ROUND_UP(dispc_freq, lck_max), 1ul);
	lckd_stop = min(dispc_freq / pck_min, 255ul);

	for (lckd = lckd_start; lckd <= lckd_stop; ++lckd) {
		lck = dispc_freq / lckd;

		pckd_start = max(DIV_ROUND_UP(lck, pck_max), pckd_hw_min);
		pckd_stop = min(lck / pck_min, pckd_hw_max);

		for (pckd = pckd_start; pckd <= pckd_stop; ++pckd) {
			pck = lck / pckd;

			/*
			 * For OMAP2/3 the DISPC fclk is the same as LCD's logic
			 * clock, which means we're configuring DISPC fclk here
			 * also. Thus we need to use the calculated lck. For
			 * OMAP4+ the DISPC fclk is a separate clock.
			 */
			if (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV))
				fck = dispc_core_clk_rate(dispc);
			else
				fck = lck;

			if (fck < pck * min_fck_per_pck)
				continue;

			if (func(lckd, pckd, lck, pck, data))
				return true;
		}
	}

	return false;
}