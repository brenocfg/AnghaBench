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
 int /*<<< orphan*/  netwinder_ds1620_set_clk (int) ; 
 int /*<<< orphan*/  netwinder_ds1620_set_data (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ds1620_send_bits(int nr, int value)
{
	int i;

	for (i = 0; i < nr; i++) {
		netwinder_ds1620_set_data(value & 1);
		netwinder_ds1620_set_clk(0);
		udelay(1);
		netwinder_ds1620_set_clk(1);
		udelay(1);

		value >>= 1;
	}
}