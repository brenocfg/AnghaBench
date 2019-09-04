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

int cache_control(unsigned int command)
{
	volatile unsigned int *p = (volatile unsigned int *) 0x80000000;
	int i;

	for (i = 0; i < (32 * 1024); i += 32) {
		(void)*p;
		p += (32 / sizeof(int));
	}

	return 0;
}