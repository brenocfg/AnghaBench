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
struct intelfb_info {TYPE_1__ ring; scalar_t__ ring_space; int /*<<< orphan*/  accel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*) ; 
 scalar_t__ RING_MIN_FREE ; 
 int /*<<< orphan*/  do_flush (struct intelfb_info*) ; 
 int /*<<< orphan*/  wait_ring (struct intelfb_info*,scalar_t__) ; 

void intelfbhw_do_sync(struct intelfb_info *dinfo)
{
#if VERBOSE > 0
	DBG_MSG("intelfbhw_do_sync\n");
#endif

	if (!dinfo->accel)
		return;

	/*
	 * Send a flush, then wait until the ring is empty.  This is what
	 * the XFree86 driver does, and actually it doesn't seem a lot worse
	 * than the recommended method (both have problems).
	 */
	do_flush(dinfo);
	wait_ring(dinfo, dinfo->ring.size - RING_MIN_FREE);
	dinfo->ring_space = dinfo->ring.size - RING_MIN_FREE;
}