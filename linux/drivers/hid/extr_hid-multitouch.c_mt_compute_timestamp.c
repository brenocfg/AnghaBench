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
struct mt_application {long prev_scantime; int timestamp; scalar_t__ scantime_logical_max; scalar_t__ jiffies; } ;
typedef  long __s32 ;

/* Variables and functions */
 unsigned long MAX_TIMESTAMP_INTERVAL ; 
 scalar_t__ jiffies ; 
 unsigned long jiffies_to_usecs (scalar_t__) ; 

__attribute__((used)) static int mt_compute_timestamp(struct mt_application *app, __s32 value)
{
	long delta = value - app->prev_scantime;
	unsigned long jdelta = jiffies_to_usecs(jiffies - app->jiffies);

	app->jiffies = jiffies;

	if (delta < 0)
		delta += app->scantime_logical_max;

	/* HID_DG_SCANTIME is expressed in 100us, we want it in us. */
	delta *= 100;

	if (jdelta > MAX_TIMESTAMP_INTERVAL)
		/* No data received for a while, resync the timestamp. */
		return 0;
	else
		return app->timestamp + delta;
}