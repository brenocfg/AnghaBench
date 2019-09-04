#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmp_clk_reset_cell {int bits; int /*<<< orphan*/  lock; scalar_t__ flags; scalar_t__ reg; int /*<<< orphan*/  clk_id; } ;
struct mmp2_clk_unit {scalar_t__ apbc_base; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ offset; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* apbc_gate_clks ; 
 struct mmp_clk_reset_cell* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_clk_reset_register (struct device_node*,struct mmp_clk_reset_cell*,int) ; 

__attribute__((used)) static void mmp2_clk_reset_init(struct device_node *np,
				struct mmp2_clk_unit *pxa_unit)
{
	struct mmp_clk_reset_cell *cells;
	int i, nr_resets;

	nr_resets = ARRAY_SIZE(apbc_gate_clks);
	cells = kcalloc(nr_resets, sizeof(*cells), GFP_KERNEL);
	if (!cells)
		return;

	for (i = 0; i < nr_resets; i++) {
		cells[i].clk_id = apbc_gate_clks[i].id;
		cells[i].reg = pxa_unit->apbc_base + apbc_gate_clks[i].offset;
		cells[i].flags = 0;
		cells[i].lock = apbc_gate_clks[i].lock;
		cells[i].bits = 0x4;
	}

	mmp_clk_reset_register(np, cells, nr_resets);
}