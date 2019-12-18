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
struct synquacer_i2c {int msg_idx; int /*<<< orphan*/  completion; scalar_t__ msg_num; int /*<<< orphan*/ * msg; scalar_t__ msg_ptr; int /*<<< orphan*/  state; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_IDLE ; 
 scalar_t__ SYNQUACER_I2C_REG_BCR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void synquacer_i2c_stop(struct synquacer_i2c *i2c, int ret)
{
	/*
	 * clear IRQ (INT=0, BER=0)
	 * set Stop Condition (MSS=0)
	 * Interrupt Disable
	 */
	writeb(0, i2c->base + SYNQUACER_I2C_REG_BCR);

	i2c->state = STATE_IDLE;

	i2c->msg_ptr = 0;
	i2c->msg = NULL;
	i2c->msg_idx++;
	i2c->msg_num = 0;
	if (ret)
		i2c->msg_idx = ret;

	complete(&i2c->completion);
}