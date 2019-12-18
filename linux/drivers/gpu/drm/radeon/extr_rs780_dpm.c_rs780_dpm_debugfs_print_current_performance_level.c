#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct radeon_ps {int vclk; int /*<<< orphan*/  dclk; } ;
struct TYPE_7__ {int reference_freq; } ;
struct TYPE_8__ {TYPE_3__ spll; } ;
struct TYPE_5__ {struct radeon_ps* current_ps; } ;
struct TYPE_6__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_4__ clock; TYPE_2__ pm; } ;
struct igp_ps {int sclk_low; int sclk_high; int /*<<< orphan*/  max_voltage; int /*<<< orphan*/  min_voltage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SPLL_FUNC_CNTL ; 
 int CURRENT_FEEDBACK_DIV_MASK ; 
 int /*<<< orphan*/  FVTHROT_STATUS_REG0 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SPLL_REF_DIV_MASK ; 
 int SPLL_REF_DIV_SHIFT ; 
 int SPLL_SW_HILEN_MASK ; 
 int SPLL_SW_HILEN_SHIFT ; 
 int SPLL_SW_LOLEN_MASK ; 
 int SPLL_SW_LOLEN_SHIFT ; 
 struct igp_ps* rs780_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 

void rs780_dpm_debugfs_print_current_performance_level(struct radeon_device *rdev,
						       struct seq_file *m)
{
	struct radeon_ps *rps = rdev->pm.dpm.current_ps;
	struct igp_ps *ps = rs780_get_ps(rps);
	u32 current_fb_div = RREG32(FVTHROT_STATUS_REG0) & CURRENT_FEEDBACK_DIV_MASK;
	u32 func_cntl = RREG32(CG_SPLL_FUNC_CNTL);
	u32 ref_div = ((func_cntl & SPLL_REF_DIV_MASK) >> SPLL_REF_DIV_SHIFT) + 1;
	u32 post_div = ((func_cntl & SPLL_SW_HILEN_MASK) >> SPLL_SW_HILEN_SHIFT) + 1 +
		((func_cntl & SPLL_SW_LOLEN_MASK) >> SPLL_SW_LOLEN_SHIFT) + 1;
	u32 sclk = (rdev->clock.spll.reference_freq * current_fb_div) /
		(post_div * ref_div);

	seq_printf(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);

	/* guess based on the current sclk */
	if (sclk < (ps->sclk_low + 500))
		seq_printf(m, "power level 0    sclk: %u vddc_index: %d\n",
			   ps->sclk_low, ps->min_voltage);
	else
		seq_printf(m, "power level 1    sclk: %u vddc_index: %d\n",
			   ps->sclk_high, ps->max_voltage);
}