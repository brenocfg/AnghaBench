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
struct TYPE_6__ {int /*<<< orphan*/  nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;
struct tegra_bpmp {TYPE_3__ rstc; TYPE_2__* dev; TYPE_1__* soc; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_resets; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int devm_reset_controller_register (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  tegra_bpmp_reset_ops ; 

int tegra_bpmp_init_resets(struct tegra_bpmp *bpmp)
{
	bpmp->rstc.ops = &tegra_bpmp_reset_ops;
	bpmp->rstc.owner = THIS_MODULE;
	bpmp->rstc.of_node = bpmp->dev->of_node;
	bpmp->rstc.nr_resets = bpmp->soc->num_resets;

	return devm_reset_controller_register(bpmp->dev, &bpmp->rstc);
}