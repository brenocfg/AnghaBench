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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static int get_temp_type(u8 src)
{
	if (src >= 0x02 && src <= 0x07)
		return 3;	/* thermal diode */
	else if (src >= 0x08 && src <= 0x18)
		return 4;	/* thermistor */
	else if (src >= 0x20 && src <= 0x2b)
		return 6;	/* PECI */
	else if (src >= 0x42 && src <= 0x49)
		return 5;

	return 0;
}