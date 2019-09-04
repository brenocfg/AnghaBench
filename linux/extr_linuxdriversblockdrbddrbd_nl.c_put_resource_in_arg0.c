#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct netlink_callback {scalar_t__* args; } ;
struct drbd_resource {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_destroy_resource ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int put_resource_in_arg0(struct netlink_callback *cb, int holder_nr)
{
	if (cb->args[0]) {
		struct drbd_resource *resource =
			(struct drbd_resource *)cb->args[0];
		kref_put(&resource->kref, drbd_destroy_resource);
	}

	return 0;
}