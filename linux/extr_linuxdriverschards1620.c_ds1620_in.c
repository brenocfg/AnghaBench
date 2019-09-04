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
 unsigned int ds1620_recv_bits (int) ; 
 int /*<<< orphan*/  ds1620_send_bits (int,int) ; 
 int /*<<< orphan*/  netwinder_ds1620_reset () ; 
 int /*<<< orphan*/  netwinder_ds1620_set_clk (int) ; 
 int /*<<< orphan*/  netwinder_ds1620_set_data_dir (int) ; 
 int /*<<< orphan*/  netwinder_lock (unsigned long*) ; 
 int /*<<< orphan*/  netwinder_unlock (unsigned long*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int ds1620_in(int cmd, int bits)
{
	unsigned long flags;
	unsigned int value;

	netwinder_lock(&flags);
	netwinder_ds1620_set_clk(1);
	netwinder_ds1620_set_data_dir(0);
	netwinder_ds1620_reset();

	udelay(1);

	ds1620_send_bits(8, cmd);

	netwinder_ds1620_set_data_dir(1);
	value = ds1620_recv_bits(bits);

	netwinder_ds1620_reset();
	netwinder_unlock(&flags);

	return value;
}