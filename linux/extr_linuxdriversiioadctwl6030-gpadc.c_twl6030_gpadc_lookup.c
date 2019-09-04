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
struct twl6030_ideal_code {int channel; } ;

/* Variables and functions */

__attribute__((used)) static int twl6030_gpadc_lookup(const struct twl6030_ideal_code *ideal,
		int channel, int size)
{
	int i;

	for (i = 0; i < size; i++)
		if (ideal[i].channel == channel)
			break;

	return i;
}