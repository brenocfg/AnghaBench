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
struct TYPE_2__ {int of_reset_n_cells; int nr_resets; int /*<<< orphan*/  of_xlate; struct device_node* of_node; int /*<<< orphan*/ * ops; } ;
struct mmp_clk_reset_unit {TYPE_1__ rcdev; struct mmp_clk_reset_cell* cells; } ;
struct mmp_clk_reset_cell {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mmp_clk_reset_unit* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_clk_reset_ops ; 
 int /*<<< orphan*/  mmp_of_reset_xlate ; 
 int /*<<< orphan*/  reset_controller_register (TYPE_1__*) ; 

void mmp_clk_reset_register(struct device_node *np,
			struct mmp_clk_reset_cell *cells, int nr_resets)
{
	struct mmp_clk_reset_unit *unit;

	unit = kzalloc(sizeof(*unit), GFP_KERNEL);
	if (!unit)
		return;

	unit->cells = cells;
	unit->rcdev.of_reset_n_cells = 1;
	unit->rcdev.nr_resets = nr_resets;
	unit->rcdev.ops = &mmp_clk_reset_ops;
	unit->rcdev.of_node = np;
	unit->rcdev.of_xlate = mmp_of_reset_xlate;

	reset_controller_register(&unit->rcdev);
}