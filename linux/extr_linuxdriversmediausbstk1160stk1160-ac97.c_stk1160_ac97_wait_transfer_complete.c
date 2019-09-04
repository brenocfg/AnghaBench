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
 int EBUSY ; 
 int /*<<< orphan*/  STK1160_AC97CTL_0 ; 
 int STK1160_AC97CTL_0_CR ; 
 int STK1160_AC97CTL_0_CW ; 
 int /*<<< orphan*/  STK1160_AC97_TIMEOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stk1160_err (char*) ; 
 int /*<<< orphan*/  stk1160_read_reg (struct stk1160*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int stk1160_ac97_wait_transfer_complete(struct stk1160 *dev)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(STK1160_AC97_TIMEOUT);
	u8 value;

	/* Wait for AC97 transfer to complete */
	while (time_is_after_jiffies(timeout)) {
		stk1160_read_reg(dev, STK1160_AC97CTL_0, &value);

		if (!(value & (STK1160_AC97CTL_0_CR | STK1160_AC97CTL_0_CW)))
			return 0;

		usleep_range(50, 100);
	}

	stk1160_err("AC97 transfer took too long, this should never happen!");
	return -EBUSY;
}