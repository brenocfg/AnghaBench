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
struct thermal_cooling_device {struct clock_cooling_device* devdata; } ;
struct clock_cooling_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LEVEL ; 
 unsigned long THERMAL_CSTATE_INVALID ; 
 scalar_t__ clock_cooling_get_property (struct clock_cooling_device*,unsigned long,unsigned long*,int /*<<< orphan*/ ) ; 

unsigned long clock_cooling_get_level(struct thermal_cooling_device *cdev,
				      unsigned long freq)
{
	struct clock_cooling_device *ccdev = cdev->devdata;
	unsigned long val;

	if (clock_cooling_get_property(ccdev, (unsigned long)freq, &val,
				       GET_LEVEL))
		return THERMAL_CSTATE_INVALID;

	return val;
}