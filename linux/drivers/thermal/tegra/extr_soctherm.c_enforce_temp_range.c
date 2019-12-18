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
struct device {int dummy; } ;

/* Variables and functions */
 int clamp_val (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  max_high_temp ; 
 int /*<<< orphan*/  min_low_temp ; 

__attribute__((used)) static int enforce_temp_range(struct device *dev, int trip_temp)
{
	int temp;

	temp = clamp_val(trip_temp, min_low_temp, max_high_temp);
	if (temp != trip_temp)
		dev_info(dev, "soctherm: trip temperature %d forced to %d\n",
			 trip_temp, temp);
	return temp;
}