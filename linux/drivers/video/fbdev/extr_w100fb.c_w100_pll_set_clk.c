#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct w100_pll_info {int /*<<< orphan*/  lock_time; int /*<<< orphan*/  N_fac; int /*<<< orphan*/  N_int; int /*<<< orphan*/  M; } ;
struct TYPE_12__ {int pwm_fast_noml_hw_en; int pwm_noml_fast_hw_en; scalar_t__ pwm_mode_req; } ;
struct TYPE_13__ {scalar_t__ val; TYPE_5__ f; } ;
struct TYPE_10__ {int /*<<< orphan*/  pll_lock_time; int /*<<< orphan*/  pll_fb_div_frac; int /*<<< orphan*/  pll_fb_div_int; int /*<<< orphan*/  pll_ref_div; } ;
struct TYPE_11__ {scalar_t__ val; TYPE_3__ f; } ;
struct TYPE_8__ {int /*<<< orphan*/  sclk_src_sel; } ;
struct TYPE_9__ {scalar_t__ val; TYPE_1__ f; } ;
struct TYPE_14__ {int auto_mode; TYPE_6__ pwrmgt_cntl; TYPE_4__ pll_ref_fb_div; TYPE_2__ sclk_cntl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SRC_XTAL ; 
 scalar_t__ mmPLL_REF_FB_DIV ; 
 scalar_t__ mmPWRMGT_CNTL ; 
 scalar_t__ mmSCLK_CNTL ; 
 scalar_t__ remapped_regs ; 
 int w100_pll_calibration (struct w100_pll_info*) ; 
 TYPE_7__ w100_pwr_state ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int w100_pll_set_clk(struct w100_pll_info *pll)
{
	int status;

	if (w100_pwr_state.auto_mode == 1)  /* auto mode */
	{
		w100_pwr_state.pwrmgt_cntl.f.pwm_fast_noml_hw_en = 0x0;  /* disable fast to normal */
		w100_pwr_state.pwrmgt_cntl.f.pwm_noml_fast_hw_en = 0x0;  /* disable normal to fast */
		writel((u32) (w100_pwr_state.pwrmgt_cntl.val), remapped_regs + mmPWRMGT_CNTL);
	}

	/* Set system clock source to XTAL whilst adjusting the PLL! */
	w100_pwr_state.sclk_cntl.f.sclk_src_sel = CLK_SRC_XTAL;
	writel((u32) (w100_pwr_state.sclk_cntl.val), remapped_regs + mmSCLK_CNTL);

	w100_pwr_state.pll_ref_fb_div.f.pll_ref_div = pll->M;
	w100_pwr_state.pll_ref_fb_div.f.pll_fb_div_int = pll->N_int;
	w100_pwr_state.pll_ref_fb_div.f.pll_fb_div_frac = pll->N_fac;
	w100_pwr_state.pll_ref_fb_div.f.pll_lock_time = pll->lock_time;
	writel((u32) (w100_pwr_state.pll_ref_fb_div.val), remapped_regs + mmPLL_REF_FB_DIV);

	w100_pwr_state.pwrmgt_cntl.f.pwm_mode_req = 0;
	writel((u32) (w100_pwr_state.pwrmgt_cntl.val), remapped_regs + mmPWRMGT_CNTL);

	status = w100_pll_calibration(pll);

	if (w100_pwr_state.auto_mode == 1)  /* auto mode */
	{
		w100_pwr_state.pwrmgt_cntl.f.pwm_fast_noml_hw_en = 0x1;  /* reenable fast to normal */
		w100_pwr_state.pwrmgt_cntl.f.pwm_noml_fast_hw_en = 0x1;  /* reenable normal to fast  */
		writel((u32) (w100_pwr_state.pwrmgt_cntl.val), remapped_regs + mmPWRMGT_CNTL);
	}
	return status;
}