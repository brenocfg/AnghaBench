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

__attribute__((used)) static int hpt37x_clock_slot(unsigned int freq, unsigned int base)
{
	unsigned int f = (base * freq) / 192;	/* Mhz */
	if (f < 40)
		return 0;	/* 33Mhz slot */
	if (f < 45)
		return 1;	/* 40Mhz slot */
	if (f < 55)
		return 2;	/* 50Mhz slot */
	return 3;		/* 60Mhz slot */
}