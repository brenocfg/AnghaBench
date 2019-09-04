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
struct edac_device_ctl_info {unsigned long poll_msec; unsigned long delay; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_mod_work (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 unsigned long round_jiffies_relative (unsigned long) ; 

void edac_device_reset_delay_period(struct edac_device_ctl_info *edac_dev,
					unsigned long value)
{
	unsigned long jiffs = msecs_to_jiffies(value);

	if (value == 1000)
		jiffs = round_jiffies_relative(value);

	edac_dev->poll_msec = value;
	edac_dev->delay	    = jiffs;

	edac_mod_work(&edac_dev->work, jiffs);
}