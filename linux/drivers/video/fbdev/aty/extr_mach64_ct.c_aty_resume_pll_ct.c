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
struct TYPE_2__ {int /*<<< orphan*/  ext_vpll_cntl; int /*<<< orphan*/  pll_ext_cntl; int /*<<< orphan*/  mclk_fb_div; int /*<<< orphan*/  pll_gen_cntl; int /*<<< orphan*/  pll_ref_div; int /*<<< orphan*/  spll_cntl2; int /*<<< orphan*/  sclk_fb_div; } ;
union aty_pll {TYPE_1__ ct; } ;
struct fb_info {struct atyfb_par* par; } ;
struct atyfb_par {scalar_t__ mclk_per; scalar_t__ xclk_per; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_VPLL_CNTL ; 
 int /*<<< orphan*/  MCLK_FB_DIV ; 
 int /*<<< orphan*/  PLL_EXT_CNTL ; 
 int /*<<< orphan*/  PLL_GEN_CNTL ; 
 int /*<<< orphan*/  PLL_REF_DIV ; 
 int /*<<< orphan*/  SCLK_FB_DIV ; 
 int /*<<< orphan*/  SPLL_CNTL2 ; 
 int /*<<< orphan*/  aty_st_pll_ct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void aty_resume_pll_ct(const struct fb_info *info,
			      union aty_pll *pll)
{
	struct atyfb_par *par = info->par;

	if (par->mclk_per != par->xclk_per) {
		/*
		* This disables the sclk, crashes the computer as reported:
		* aty_st_pll_ct(SPLL_CNTL2, 3, info);
		*
		* So it seems the sclk must be enabled before it is used;
		* so PLL_GEN_CNTL must be programmed *after* the sclk.
		*/
		aty_st_pll_ct(SCLK_FB_DIV, pll->ct.sclk_fb_div, par);
		aty_st_pll_ct(SPLL_CNTL2, pll->ct.spll_cntl2, par);
		/*
		 * SCLK has been started. Wait for the PLL to lock. 5 ms
		 * should be enough according to mach64 programmer's guide.
		 */
		mdelay(5);
	}

	aty_st_pll_ct(PLL_REF_DIV, pll->ct.pll_ref_div, par);
	aty_st_pll_ct(PLL_GEN_CNTL, pll->ct.pll_gen_cntl, par);
	aty_st_pll_ct(MCLK_FB_DIV, pll->ct.mclk_fb_div, par);
	aty_st_pll_ct(PLL_EXT_CNTL, pll->ct.pll_ext_cntl, par);
	aty_st_pll_ct(EXT_VPLL_CNTL, pll->ct.ext_vpll_cntl, par);
}