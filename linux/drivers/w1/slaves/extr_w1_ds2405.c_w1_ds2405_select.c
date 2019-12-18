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
typedef  int u64 ;
struct w1_slave {int /*<<< orphan*/  reg_num; struct w1_master* master; } ;
struct w1_master {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  W1_ALARM_SEARCH ; 
 int /*<<< orphan*/  W1_SEARCH ; 
 int le64_to_cpu (int) ; 
 scalar_t__ w1_reset_bus (struct w1_master*) ; 
 int w1_triplet (struct w1_master*,int) ; 
 int /*<<< orphan*/  w1_write_8 (struct w1_master*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w1_ds2405_select(struct w1_slave *sl, bool only_active)
{
	struct w1_master *dev = sl->master;

	u64 dev_addr = le64_to_cpu(*(u64 *)&sl->reg_num);
	unsigned int bit_ctr;

	if (w1_reset_bus(dev) != 0)
		return 0;

	/*
	 * We cannot use a normal Match ROM command
	 * since doing so would toggle PIO state
	 */
	w1_write_8(dev, only_active ? W1_ALARM_SEARCH : W1_SEARCH);

	for (bit_ctr = 0; bit_ctr < 64; bit_ctr++) {
		int bit2send = !!(dev_addr & BIT(bit_ctr));
		u8 ret;

		ret = w1_triplet(dev, bit2send);

		if ((ret & (BIT(0) | BIT(1))) ==
		    (BIT(0) | BIT(1))) /* no devices found */
			return 0;

		if (!!(ret & BIT(2)) != bit2send)
			/* wrong direction taken - no such device */
			return 0;
	}

	return 1;
}