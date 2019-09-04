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
struct drbd_interval {int sector; int size; } ;
struct drbd_device {int /*<<< orphan*/  local_cnt; } ;

/* Variables and functions */
 int AL_EXTENT_SHIFT ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 int _al_get (struct drbd_device*,unsigned int,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

bool drbd_al_begin_io_fastpath(struct drbd_device *device, struct drbd_interval *i)
{
	/* for bios crossing activity log extent boundaries,
	 * we may need to activate two extents in one go */
	unsigned first = i->sector >> (AL_EXTENT_SHIFT-9);
	unsigned last = i->size == 0 ? first : (i->sector + (i->size >> 9) - 1) >> (AL_EXTENT_SHIFT-9);

	D_ASSERT(device, first <= last);
	D_ASSERT(device, atomic_read(&device->local_cnt) > 0);

	/* FIXME figure out a fast path for bios crossing AL extent boundaries */
	if (first != last)
		return false;

	return _al_get(device, first, true);
}