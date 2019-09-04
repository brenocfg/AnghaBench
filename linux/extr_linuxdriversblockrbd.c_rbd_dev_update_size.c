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
struct TYPE_2__ {scalar_t__ size; } ;
struct rbd_device {int /*<<< orphan*/  disk; TYPE_1__ mapping; int /*<<< orphan*/  flags; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  RBD_DEV_FLAG_EXISTS ; 
 int /*<<< orphan*/  RBD_DEV_FLAG_REMOVING ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  dout (char*,unsigned long long) ; 
 int /*<<< orphan*/  revalidate_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_dev_update_size(struct rbd_device *rbd_dev)
{
	sector_t size;

	/*
	 * If EXISTS is not set, rbd_dev->disk may be NULL, so don't
	 * try to update its size.  If REMOVING is set, updating size
	 * is just useless work since the device can't be opened.
	 */
	if (test_bit(RBD_DEV_FLAG_EXISTS, &rbd_dev->flags) &&
	    !test_bit(RBD_DEV_FLAG_REMOVING, &rbd_dev->flags)) {
		size = (sector_t)rbd_dev->mapping.size / SECTOR_SIZE;
		dout("setting size to %llu sectors", (unsigned long long)size);
		set_capacity(rbd_dev->disk, size);
		revalidate_disk(rbd_dev->disk);
	}
}