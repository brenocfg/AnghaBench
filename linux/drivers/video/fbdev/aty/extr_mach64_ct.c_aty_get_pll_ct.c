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
struct TYPE_2__ {int vclk_post_div; int pll_ext_cntl; int vclk_fb_div; int pll_ref_div; int mclk_fb_div; int pll_gen_cntl; int pll_vclk_cntl; void* dsp_on_off; void* dsp_config; } ;
union aty_pll {TYPE_1__ ct; } ;
typedef  int u8 ;
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CNTL ; 
 int /*<<< orphan*/  DSP_CONFIG ; 
 int /*<<< orphan*/  DSP_ON_OFF ; 
 int /*<<< orphan*/  GTB_DSP ; 
 scalar_t__ M64_HAS (int /*<<< orphan*/ ) ; 
 scalar_t__ MCLK_FB_DIV ; 
 scalar_t__ PLL_EXT_CNTL ; 
 scalar_t__ PLL_GEN_CNTL ; 
 scalar_t__ PLL_REF_DIV ; 
 scalar_t__ PLL_VCLK_CNTL ; 
 scalar_t__ VCLK0_FB_DIV ; 
 scalar_t__ VCLK_POST_DIV ; 
 int aty_ld_8 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 void* aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int aty_ld_pll_ct (scalar_t__,struct atyfb_par*) ; 

__attribute__((used)) static void aty_get_pll_ct(const struct fb_info *info, union aty_pll *pll)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u8 tmp, clock;

	clock = aty_ld_8(CLOCK_CNTL, par) & 0x03U;
	tmp = clock << 1;
	pll->ct.vclk_post_div = (aty_ld_pll_ct(VCLK_POST_DIV, par) >> tmp) & 0x03U;

	pll->ct.pll_ext_cntl = aty_ld_pll_ct(PLL_EXT_CNTL, par) & 0x0FU;
	pll->ct.vclk_fb_div = aty_ld_pll_ct(VCLK0_FB_DIV + clock, par) & 0xFFU;
	pll->ct.pll_ref_div = aty_ld_pll_ct(PLL_REF_DIV, par);
	pll->ct.mclk_fb_div = aty_ld_pll_ct(MCLK_FB_DIV, par);

	pll->ct.pll_gen_cntl = aty_ld_pll_ct(PLL_GEN_CNTL, par);
	pll->ct.pll_vclk_cntl = aty_ld_pll_ct(PLL_VCLK_CNTL, par);

	if (M64_HAS(GTB_DSP)) {
		pll->ct.dsp_config = aty_ld_le32(DSP_CONFIG, par);
		pll->ct.dsp_on_off = aty_ld_le32(DSP_ON_OFF, par);
	}
}