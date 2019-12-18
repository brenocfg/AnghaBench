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
struct vsoc_device_region {int dummy; } ;
struct fd_scoped_permission_node {int /*<<< orphan*/  list; int /*<<< orphan*/  permission; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_destroy_fd_scoped_permission (struct vsoc_device_region*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fd_scoped_permission_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ vsoc_dev ; 

__attribute__((used)) static void
do_destroy_fd_scoped_permission_node(struct vsoc_device_region *owner_region_p,
				     struct fd_scoped_permission_node *node)
{
	if (node) {
		do_destroy_fd_scoped_permission(owner_region_p,
						&node->permission);
		mutex_lock(&vsoc_dev.mtx);
		list_del(&node->list);
		mutex_unlock(&vsoc_dev.mtx);
		kfree(node);
	}
}