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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ NI_DCIO_UNIPHY0_PLL_CONTROL1 ; 
 unsigned int NI_DCIO_UNIPHY0_PLL_CONTROL1_ENABLE ; 
 scalar_t__ NI_DIG_BE_CNTL ; 
 unsigned int NI_DIG_BE_CNTL_FE_SOURCE_SELECT (unsigned int) ; 
 unsigned int NI_DIG_BE_DPSST ; 
 scalar_t__ NI_DIG_BE_EN_CNTL ; 
 unsigned int NI_DIG_BE_EN_CNTL_ENABLE ; 
 unsigned int NI_DIG_BE_EN_CNTL_SYMBCLK_ON ; 
 scalar_t__ NI_DIG_FE_CNTL ; 
 unsigned int NI_DIG_FE_CNTL_MODE (unsigned int) ; 
 unsigned int NI_DIG_FE_CNTL_SOURCE_SELECT (unsigned int) ; 
 unsigned int NI_DIG_FE_CNTL_SYMCLK_FE_ON ; 
 unsigned int RREG32 (scalar_t__) ; 
 scalar_t__* ni_dig_offsets ; 
 scalar_t__* ni_tx_offsets ; 

__attribute__((used)) static bool evergreen_is_dp_sst_stream_enabled(struct radeon_device *rdev,
					       unsigned crtc_id, unsigned *ret_dig_fe)
{
	unsigned i;
	unsigned dig_fe;
	unsigned dig_be;
	unsigned dig_en_be;
	unsigned uniphy_pll;
	unsigned digs_fe_selected;
	unsigned dig_be_mode;
	unsigned dig_fe_mask;
	bool is_enabled = false;
	bool found_crtc = false;

	/* loop through all running dig_fe to find selected crtc */
	for (i = 0; i < ARRAY_SIZE(ni_dig_offsets); i++) {
		dig_fe = RREG32(NI_DIG_FE_CNTL + ni_dig_offsets[i]);
		if (dig_fe & NI_DIG_FE_CNTL_SYMCLK_FE_ON &&
		    crtc_id == NI_DIG_FE_CNTL_SOURCE_SELECT(dig_fe)) {
			/* found running pipe */
			found_crtc = true;
			dig_fe_mask = 1 << i;
			dig_fe = i;
			break;
		}
	}

	if (found_crtc) {
		/* loop through all running dig_be to find selected dig_fe */
		for (i = 0; i < ARRAY_SIZE(ni_dig_offsets); i++) {
			dig_be = RREG32(NI_DIG_BE_CNTL + ni_dig_offsets[i]);
			/* if dig_fe_selected by dig_be? */
			digs_fe_selected = NI_DIG_BE_CNTL_FE_SOURCE_SELECT(dig_be);
			dig_be_mode = NI_DIG_FE_CNTL_MODE(dig_be);
			if (dig_fe_mask &  digs_fe_selected &&
			    /* if dig_be in sst mode? */
			    dig_be_mode == NI_DIG_BE_DPSST) {
				dig_en_be = RREG32(NI_DIG_BE_EN_CNTL +
						   ni_dig_offsets[i]);
				uniphy_pll = RREG32(NI_DCIO_UNIPHY0_PLL_CONTROL1 +
						    ni_tx_offsets[i]);
				/* dig_be enable and tx is running */
				if (dig_en_be & NI_DIG_BE_EN_CNTL_ENABLE &&
				    dig_en_be & NI_DIG_BE_EN_CNTL_SYMBCLK_ON &&
				    uniphy_pll & NI_DCIO_UNIPHY0_PLL_CONTROL1_ENABLE) {
					is_enabled = true;
					*ret_dig_fe = dig_fe;
					break;
				}
			}
		}
	}

	return is_enabled;
}