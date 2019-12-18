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
struct stk1160 {int dummy; } ;

/* Variables and functions */
 scalar_t__ STK1160_AC97CTL_0 ; 
 scalar_t__ STK1160_AC97_ADDR ; 
 scalar_t__ STK1160_AC97_CMD ; 
 int /*<<< orphan*/  stk1160_ac97_wait_transfer_complete (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_write_reg (struct stk1160*,scalar_t__,int) ; 

__attribute__((used)) static void stk1160_write_ac97(struct stk1160 *dev, u16 reg, u16 value)
{
	/* Set codec register address */
	stk1160_write_reg(dev, STK1160_AC97_ADDR, reg);

	/* Set codec command */
	stk1160_write_reg(dev, STK1160_AC97_CMD, value & 0xff);
	stk1160_write_reg(dev, STK1160_AC97_CMD + 1, (value & 0xff00) >> 8);

	/* Set command write bit to initiate write operation */
	stk1160_write_reg(dev, STK1160_AC97CTL_0, 0x8c);

	/* Wait for command write bit to be cleared */
	stk1160_ac97_wait_transfer_complete(dev);
}