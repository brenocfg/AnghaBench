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
struct rbd_device {scalar_t__ parent_overlap; int /*<<< orphan*/ * parent_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbd_dev_remove_parent (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_spec_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_dev_unparent(struct rbd_device *rbd_dev)
{
	rbd_dev_remove_parent(rbd_dev);
	rbd_spec_put(rbd_dev->parent_spec);
	rbd_dev->parent_spec = NULL;
	rbd_dev->parent_overlap = 0;
}