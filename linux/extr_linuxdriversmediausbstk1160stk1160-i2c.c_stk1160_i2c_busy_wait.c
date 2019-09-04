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
struct stk1160 {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STK1160_I2C_TIMEOUT ; 
 scalar_t__ STK1160_SICTL ; 
 int USEC_PER_MSEC ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stk1160_read_reg (struct stk1160*,scalar_t__,int*) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int stk1160_i2c_busy_wait(struct stk1160 *dev, u8 wait_bit_mask)
{
	unsigned long end;
	u8 flag;

	/* Wait until read/write finish bit is set */
	end = jiffies + msecs_to_jiffies(STK1160_I2C_TIMEOUT);
	while (time_is_after_jiffies(end)) {

		stk1160_read_reg(dev, STK1160_SICTL+1, &flag);
		/* read/write done? */
		if (flag & wait_bit_mask)
			goto done;

		usleep_range(10 * USEC_PER_MSEC, 20 * USEC_PER_MSEC);
	}

	return -ETIMEDOUT;

done:
	return 0;
}