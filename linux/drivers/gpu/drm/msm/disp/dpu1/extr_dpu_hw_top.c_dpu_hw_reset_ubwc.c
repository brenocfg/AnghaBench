#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dpu_mdss_cfg {TYPE_2__* mdp; TYPE_1__* caps; } ;
struct dpu_hw_blk_reg_map {int blk_off; } ;
struct dpu_hw_mdp {struct dpu_hw_blk_reg_map hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  ubwc_static; } ;
struct TYPE_3__ {int /*<<< orphan*/  ubwc_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_UBWC_20_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UBWC_STATIC ; 

__attribute__((used)) static void dpu_hw_reset_ubwc(struct dpu_hw_mdp *mdp, struct dpu_mdss_cfg *m)
{
	struct dpu_hw_blk_reg_map c;

	if (!mdp || !m)
		return;

	if (!IS_UBWC_20_SUPPORTED(m->caps->ubwc_version))
		return;

	/* force blk offset to zero to access beginning of register region */
	c = mdp->hw;
	c.blk_off = 0x0;
	DPU_REG_WRITE(&c, UBWC_STATIC, m->mdp[0].ubwc_static);
}