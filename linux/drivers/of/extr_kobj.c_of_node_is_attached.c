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
struct TYPE_2__ {scalar_t__ state_in_sysfs; } ;
struct device_node {TYPE_1__ kobj; } ;

/* Variables and functions */

int of_node_is_attached(struct device_node *node)
{
	return node && node->kobj.state_in_sysfs;
}