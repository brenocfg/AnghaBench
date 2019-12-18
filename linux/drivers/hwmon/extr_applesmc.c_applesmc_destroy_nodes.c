#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct applesmc_node_group {struct applesmc_dev_attr* nodes; } ;
struct TYPE_9__ {scalar_t__ name; } ;
struct TYPE_7__ {TYPE_4__ attr; } ;
struct TYPE_8__ {TYPE_2__ dev_attr; } ;
struct applesmc_dev_attr {TYPE_3__ sda; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct applesmc_dev_attr*) ; 
 TYPE_5__* pdev ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void applesmc_destroy_nodes(struct applesmc_node_group *groups)
{
	struct applesmc_node_group *grp;
	struct applesmc_dev_attr *node;

	for (grp = groups; grp->nodes; grp++) {
		for (node = grp->nodes; node->sda.dev_attr.attr.name; node++)
			sysfs_remove_file(&pdev->dev.kobj,
					  &node->sda.dev_attr.attr);
		kfree(grp->nodes);
		grp->nodes = NULL;
	}
}