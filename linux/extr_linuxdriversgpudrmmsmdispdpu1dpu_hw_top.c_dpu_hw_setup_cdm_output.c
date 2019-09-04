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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_mdp {struct dpu_hw_blk_reg_map hw; } ;
struct cdm_output_cfg {scalar_t__ intf_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDP_OUT_CTL_0 ; 

__attribute__((used)) static void dpu_hw_setup_cdm_output(struct dpu_hw_mdp *mdp,
		struct cdm_output_cfg *cfg)
{
	struct dpu_hw_blk_reg_map *c;
	u32 out_ctl = 0;

	if (!mdp || !cfg)
		return;

	c = &mdp->hw;

	if (cfg->intf_en)
		out_ctl |= BIT(19);

	DPU_REG_WRITE(c, MDP_OUT_CTL_0, out_ctl);
}