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
struct cx25840_ir_state {int /*<<< orphan*/  rx_params_lock; TYPE_1__ rx_params; struct i2c_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_EDG_NONE ; 
 int /*<<< orphan*/  CX25840_IR_RXCLK_REG ; 
 int ENODEV ; 
 int /*<<< orphan*/  RXCLK_RCD ; 
 int /*<<< orphan*/  control_rx_demodulation_enable (struct i2c_client*,int) ; 
 int /*<<< orphan*/  control_rx_enable (struct i2c_client*,int) ; 
 int /*<<< orphan*/  control_rx_s_edge_detection (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_rx_s_min_width (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqenable_rx (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cx25840_ir_state* to_ir_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_ir_rx_shutdown(struct v4l2_subdev *sd)
{
	struct cx25840_ir_state *ir_state = to_ir_state(sd);
	struct i2c_client *c;

	if (ir_state == NULL)
		return -ENODEV;

	c = ir_state->c;
	mutex_lock(&ir_state->rx_params_lock);

	/* Disable or slow down all IR Rx circuits and counters */
	irqenable_rx(sd, 0);
	control_rx_enable(c, false);
	control_rx_demodulation_enable(c, false);
	control_rx_s_edge_detection(c, CNTRL_EDG_NONE);
	filter_rx_s_min_width(c, 0);
	cx25840_write4(c, CX25840_IR_RXCLK_REG, RXCLK_RCD);

	ir_state->rx_params.shutdown = true;

	mutex_unlock(&ir_state->rx_params_lock);
	return 0;
}