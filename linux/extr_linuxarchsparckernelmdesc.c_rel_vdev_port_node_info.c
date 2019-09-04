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
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;
union md_node_info {TYPE_1__ vdev_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rel_vdev_port_node_info(union md_node_info *node_info)
{
	if (node_info && node_info->vdev_port.name) {
		kfree_const(node_info->vdev_port.name);
		node_info->vdev_port.name = NULL;
	}
}