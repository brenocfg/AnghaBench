#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int shutdown; } ;
struct cx25840_ir_state {int /*<<< orphan*/  tx_params_lock; TYPE_1__ tx_params; struct i2c_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX25840_IR_TXCLK_REG ; 
 int ENODEV ; 
 int /*<<< orphan*/  TXCLK_TCD ; 
 int /*<<< orphan*/  control_tx_enable (struct i2c_client*,int) ; 
 int /*<<< orphan*/  control_tx_modulation_enable (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqenable_tx (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cx25840_ir_state* to_ir_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_ir_tx_shutdown(struct v4l2_subdev *sd)
{
	struct cx25840_ir_state *ir_state = to_ir_state(sd);
	struct i2c_client *c;

	if (ir_state == NULL)
		return -ENODEV;

	c = ir_state->c;
	mutex_lock(&ir_state->tx_params_lock);

	/* Disable or slow down all IR Tx circuits and counters */
	irqenable_tx(sd, 0);
	control_tx_enable(c, false);
	control_tx_modulation_enable(c, false);
	cx25840_write4(c, CX25840_IR_TXCLK_REG, TXCLK_TCD);

	ir_state->tx_params.shutdown = true;

	mutex_unlock(&ir_state->tx_params_lock);
	return 0;
}