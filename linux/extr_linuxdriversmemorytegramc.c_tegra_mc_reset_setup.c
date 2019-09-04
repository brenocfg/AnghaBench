#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int of_reset_n_cells; int /*<<< orphan*/  nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;
struct tegra_mc {TYPE_3__ reset; TYPE_2__* soc; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_resets; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int reset_controller_register (TYPE_3__*) ; 
 int /*<<< orphan*/  tegra_mc_reset_ops ; 

__attribute__((used)) static int tegra_mc_reset_setup(struct tegra_mc *mc)
{
	int err;

	mc->reset.ops = &tegra_mc_reset_ops;
	mc->reset.owner = THIS_MODULE;
	mc->reset.of_node = mc->dev->of_node;
	mc->reset.of_reset_n_cells = 1;
	mc->reset.nr_resets = mc->soc->num_resets;

	err = reset_controller_register(&mc->reset);
	if (err < 0)
		return err;

	return 0;
}