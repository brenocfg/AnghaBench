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
struct vchiq_debugfs_node {int dummy; } ;
typedef  TYPE_1__* VCHIQ_INSTANCE_T ;
struct TYPE_3__ {struct vchiq_debugfs_node debugfs_node; } ;

/* Variables and functions */

struct vchiq_debugfs_node *
vchiq_instance_get_debugfs_node(VCHIQ_INSTANCE_T instance)
{
	return &instance->debugfs_node;
}