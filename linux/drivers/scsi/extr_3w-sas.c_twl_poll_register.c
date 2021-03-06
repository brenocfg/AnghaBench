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
typedef  int u32 ;
typedef  int /*<<< orphan*/  TW_Device_Extension ;

/* Variables and functions */
 int HZ ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (void*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int twl_poll_register(TW_Device_Extension *tw_dev, void *reg, u32 value, u32 result, int seconds)
{
	unsigned long before;
	int retval = 1;
	u32 reg_value;

	reg_value = readl(reg);
	before = jiffies;

        while ((reg_value & value) != result) {
		reg_value = readl(reg);
		if (time_after(jiffies, before + HZ * seconds))
			goto out;
		msleep(50);
	}
	retval = 0;
out:
	return retval;
}