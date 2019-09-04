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
struct pt3_board {scalar_t__* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT3_I2C_RESET ; 
 scalar_t__ REG_I2C_W ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

void pt3_i2c_reset(struct pt3_board *pt3)
{
	iowrite32(PT3_I2C_RESET, pt3->regs[0] + REG_I2C_W);
}