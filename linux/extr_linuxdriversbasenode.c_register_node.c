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
struct TYPE_3__ {int id; int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; } ;
struct node {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  compaction_register_node (struct node*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  hugetlb_register_node (struct node*) ; 
 int /*<<< orphan*/  node_dev_groups ; 
 int /*<<< orphan*/  node_device_release ; 
 int /*<<< orphan*/  node_subsys ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static int register_node(struct node *node, int num)
{
	int error;

	node->dev.id = num;
	node->dev.bus = &node_subsys;
	node->dev.release = node_device_release;
	node->dev.groups = node_dev_groups;
	error = device_register(&node->dev);

	if (error)
		put_device(&node->dev);
	else {
		hugetlb_register_node(node);

		compaction_register_node(node);
	}
	return error;
}