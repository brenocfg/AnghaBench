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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int,int) ; 

void ams_delta_latch_write(int base, int ngpio, u16 mask, u16 value)
{
	int bit = 0;
	u16 bitpos = 1 << bit;

	for (; bit < ngpio; bit++, bitpos = bitpos << 1) {
		if (!(mask & bitpos))
			continue;
		else
			gpio_set_value(base + bit, (value & bitpos) != 0);
	}
}