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
struct clock_cooling_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FREQ ; 
 int clock_cooling_get_property (struct clock_cooling_device*,unsigned long,unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
clock_cooling_get_frequency(struct clock_cooling_device *ccdev,
			    unsigned long level)
{
	int ret = 0;
	unsigned long freq;

	ret = clock_cooling_get_property(ccdev, level, &freq, GET_FREQ);
	if (ret)
		return 0;

	return freq;
}