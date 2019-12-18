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
typedef  int u32 ;
struct radeonfb_info {scalar_t__ is_mobility; int /*<<< orphan*/  asleep; scalar_t__ has_CRTC2; } ;
struct fb_info {struct radeonfb_info* par; } ;

/* Variables and functions */
 int DAC2_PALETTE_ACCESS_CNTL ; 
 int /*<<< orphan*/  DAC_CNTL2 ; 
 int INPLL (int /*<<< orphan*/ ) ; 
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTPLL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int PIXCLK_DAC_ALWAYS_ONb ; 
 int /*<<< orphan*/  VCLK_ECP_CNTL ; 
 int radeon_setcolreg (unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,struct radeonfb_info*) ; 

__attribute__((used)) static int radeonfb_setcolreg (unsigned regno, unsigned red, unsigned green,
			       unsigned blue, unsigned transp,
			       struct fb_info *info)
{
        struct radeonfb_info *rinfo = info->par;
	u32 dac_cntl2, vclk_cntl = 0;
	int rc;

        if (!rinfo->asleep) {
		if (rinfo->is_mobility) {
			vclk_cntl = INPLL(VCLK_ECP_CNTL);
			OUTPLL(VCLK_ECP_CNTL,
			       vclk_cntl & ~PIXCLK_DAC_ALWAYS_ONb);
		}

		/* Make sure we are on first palette */
		if (rinfo->has_CRTC2) {
			dac_cntl2 = INREG(DAC_CNTL2);
			dac_cntl2 &= ~DAC2_PALETTE_ACCESS_CNTL;
			OUTREG(DAC_CNTL2, dac_cntl2);
		}
	}

	rc = radeon_setcolreg (regno, red, green, blue, transp, rinfo);

	if (!rinfo->asleep && rinfo->is_mobility)
		OUTPLL(VCLK_ECP_CNTL, vclk_cntl);

	return rc;
}