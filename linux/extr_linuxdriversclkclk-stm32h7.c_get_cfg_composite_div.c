#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct composite_clk_gcfg {TYPE_6__* gate; TYPE_4__* div; TYPE_2__* mux; } ;
struct composite_clk_cfg {TYPE_5__* gate; TYPE_3__* div; TYPE_1__* mux; } ;
struct composite_cfg {struct clk_ops const* gate_ops; struct clk_hw* gate_hw; struct clk_ops const* div_ops; struct clk_hw* div_hw; struct clk_ops const* mux_ops; struct clk_hw* mux_hw; } ;
struct clk_ops {int dummy; } ;
struct clk_hw {int dummy; } ;
struct clk_mux {struct clk_hw hw; } ;
struct clk_gate {struct clk_hw hw; } ;
struct clk_divider {struct clk_hw hw; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_12__ {struct clk_ops* ops; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  bit_idx; scalar_t__ offset; } ;
struct TYPE_10__ {struct clk_ops* ops; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  width; int /*<<< orphan*/  shift; scalar_t__ offset; } ;
struct TYPE_8__ {struct clk_ops* ops; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  width; int /*<<< orphan*/  shift; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk_mux*) ; 
 struct clk_mux* _get_cdiv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_mux* _get_cgate (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_mux* _get_cmux (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ base ; 
 struct clk_ops clk_divider_ops ; 
 struct clk_ops clk_gate_ops ; 
 struct clk_ops clk_mux_ops ; 

__attribute__((used)) static void get_cfg_composite_div(const struct composite_clk_gcfg *gcfg,
		const struct composite_clk_cfg *cfg,
		struct composite_cfg *composite, spinlock_t *lock)
{
	struct clk_mux     *mux = NULL;
	struct clk_divider *div = NULL;
	struct clk_gate    *gate = NULL;
	const struct clk_ops *mux_ops, *div_ops, *gate_ops;
	struct clk_hw *mux_hw;
	struct clk_hw *div_hw;
	struct clk_hw *gate_hw;

	mux_ops = div_ops = gate_ops = NULL;
	mux_hw = div_hw = gate_hw = NULL;

	if (gcfg->mux && cfg->mux) {
		mux = _get_cmux(base + cfg->mux->offset,
				cfg->mux->shift,
				cfg->mux->width,
				gcfg->mux->flags, lock);

		if (!IS_ERR(mux)) {
			mux_hw = &mux->hw;
			mux_ops = gcfg->mux->ops ?
				  gcfg->mux->ops : &clk_mux_ops;
		}
	}

	if (gcfg->div && cfg->div) {
		div = _get_cdiv(base + cfg->div->offset,
				cfg->div->shift,
				cfg->div->width,
				gcfg->div->flags, lock);

		if (!IS_ERR(div)) {
			div_hw = &div->hw;
			div_ops = gcfg->div->ops ?
				  gcfg->div->ops : &clk_divider_ops;
		}
	}

	if (gcfg->gate && cfg->gate) {
		gate = _get_cgate(base + cfg->gate->offset,
				cfg->gate->bit_idx,
				gcfg->gate->flags, lock);

		if (!IS_ERR(gate)) {
			gate_hw = &gate->hw;
			gate_ops = gcfg->gate->ops ?
				   gcfg->gate->ops : &clk_gate_ops;
		}
	}

	composite->mux_hw = mux_hw;
	composite->mux_ops = mux_ops;

	composite->div_hw = div_hw;
	composite->div_ops = div_ops;

	composite->gate_hw = gate_hw;
	composite->gate_ops = gate_ops;
}