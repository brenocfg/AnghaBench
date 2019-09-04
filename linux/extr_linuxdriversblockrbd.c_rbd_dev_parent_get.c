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
struct rbd_device {int /*<<< orphan*/  header_rwsem; int /*<<< orphan*/  parent_ref; scalar_t__ parent_overlap; int /*<<< orphan*/  parent_spec; } ;

/* Variables and functions */
 int atomic_inc_return_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rbd_dev_parent_get(struct rbd_device *rbd_dev)
{
	int counter = 0;

	if (!rbd_dev->parent_spec)
		return false;

	down_read(&rbd_dev->header_rwsem);
	if (rbd_dev->parent_overlap)
		counter = atomic_inc_return_safe(&rbd_dev->parent_ref);
	up_read(&rbd_dev->header_rwsem);

	if (counter < 0)
		rbd_warn(rbd_dev, "parent reference overflow");

	return counter > 0;
}