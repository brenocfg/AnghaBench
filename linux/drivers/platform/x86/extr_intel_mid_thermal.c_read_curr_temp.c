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
struct thermal_zone_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int mid_read_temp (struct thermal_zone_device*,int*) ; 

__attribute__((used)) static int read_curr_temp(struct thermal_zone_device *tzd, int *temp)
{
	WARN_ON(tzd == NULL);
	return mid_read_temp(tzd, temp);
}