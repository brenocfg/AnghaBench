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
 int ARRAY_SIZE (unsigned int*) ; 

__attribute__((used)) static int veml6070_to_uv_index(unsigned val)
{
	/*
	 * conversion of raw UV intensity values to UV index depends on
	 * integration time (IT) and value of the resistor connected to
	 * the RSET pin (default: 270 KOhm)
	 */
	unsigned uvi[11] = {
		187, 373, 560, /* low */
		746, 933, 1120, /* moderate */
		1308, 1494, /* high */
		1681, 1868, 2054}; /* very high */
	int i;

	for (i = 0; i < ARRAY_SIZE(uvi); i++)
		if (val <= uvi[i])
			return i;

	return 11; /* extreme */
}