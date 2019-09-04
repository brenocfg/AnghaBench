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
typedef  int u8 ;
struct clk_omap_reg {int dummy; } ;
struct clk_hw_omap {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_4__ {int (* clk_readl ) (struct clk_omap_reg*) ;int (* cm_split_idlest_reg ) (struct clk_omap_reg*,int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* cm_wait_module_ready ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* find_idlest ) (struct clk_hw_omap*,struct clk_omap_reg*,int*,int*) ;int /*<<< orphan*/  (* find_companion ) (struct clk_hw_omap*,struct clk_omap_reg*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _wait_idlest_generic (struct clk_hw_omap*,struct clk_omap_reg*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct clk_hw_omap*,struct clk_omap_reg*,int*) ; 
 int stub2 (struct clk_omap_reg*) ; 
 int /*<<< orphan*/  stub3 (struct clk_hw_omap*,struct clk_omap_reg*,int*,int*) ; 
 int stub4 (struct clk_omap_reg*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* ti_clk_ll_ops ; 

__attribute__((used)) static void _omap2_module_wait_ready(struct clk_hw_omap *clk)
{
	struct clk_omap_reg companion_reg, idlest_reg;
	u8 other_bit, idlest_bit, idlest_val, idlest_reg_id;
	s16 prcm_mod;
	int r;

	/* Not all modules have multiple clocks that their IDLEST depends on */
	if (clk->ops->find_companion) {
		clk->ops->find_companion(clk, &companion_reg, &other_bit);
		if (!(ti_clk_ll_ops->clk_readl(&companion_reg) &
		      (1 << other_bit)))
			return;
	}

	clk->ops->find_idlest(clk, &idlest_reg, &idlest_bit, &idlest_val);
	r = ti_clk_ll_ops->cm_split_idlest_reg(&idlest_reg, &prcm_mod,
					       &idlest_reg_id);
	if (r) {
		/* IDLEST register not in the CM module */
		_wait_idlest_generic(clk, &idlest_reg, (1 << idlest_bit),
				     idlest_val, clk_hw_get_name(&clk->hw));
	} else {
		ti_clk_ll_ops->cm_wait_module_ready(0, prcm_mod, idlest_reg_id,
						    idlest_bit);
	}
}