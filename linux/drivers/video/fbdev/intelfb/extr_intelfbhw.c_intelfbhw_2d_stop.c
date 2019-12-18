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
struct intelfb_info {scalar_t__ ring_active; int /*<<< orphan*/  accel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  reset_state (struct intelfb_info*) ; 

void intelfbhw_2d_stop(struct intelfb_info *dinfo)
{
#if VERBOSE > 0
	DBG_MSG("intelfbhw_2d_stop: accel: %d, ring_active: %d\n",
		dinfo->accel, dinfo->ring_active);
#endif

	if (!dinfo->accel)
		return;

	dinfo->ring_active = 0;
	reset_state(dinfo);
}