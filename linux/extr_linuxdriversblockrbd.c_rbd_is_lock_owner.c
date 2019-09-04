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
struct rbd_device {int /*<<< orphan*/  lock_rwsem; } ;

/* Variables and functions */
 int __rbd_is_lock_owner (struct rbd_device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rbd_is_lock_owner(struct rbd_device *rbd_dev)
{
	bool is_lock_owner;

	down_read(&rbd_dev->lock_rwsem);
	is_lock_owner = __rbd_is_lock_owner(rbd_dev);
	up_read(&rbd_dev->lock_rwsem);
	return is_lock_owner;
}