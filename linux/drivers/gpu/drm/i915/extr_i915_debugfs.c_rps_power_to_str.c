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

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
#define  BETWEEN 130 
#define  HIGH_POWER 129 
#define  LOW_POWER 128 

__attribute__((used)) static const char *rps_power_to_str(unsigned int power)
{
	static const char * const strings[] = {
		[LOW_POWER] = "low power",
		[BETWEEN] = "mixed",
		[HIGH_POWER] = "high power",
	};

	if (power >= ARRAY_SIZE(strings) || !strings[power])
		return "unknown";

	return strings[power];
}