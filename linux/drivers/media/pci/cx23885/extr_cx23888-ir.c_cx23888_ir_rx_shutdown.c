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
struct TYPE_2__ {int shutdown; } ;
struct cx23888_ir_state {int /*<<< orphan*/  rx_params_lock; TYPE_1__ rx_params; struct cx23885_dev* dev; } ;
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_EDG_NONE ; 
 int /*<<< orphan*/  CX23888_IR_RXCLK_REG ; 
 int /*<<< orphan*/  RXCLK_RCD ; 
 int /*<<< orphan*/  control_rx_demodulation_enable (struct cx23885_dev*,int) ; 
 int /*<<< orphan*/  control_rx_enable (struct cx23885_dev*,int) ; 
 int /*<<< orphan*/  control_rx_s_edge_detection (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23888_ir_write4 (struct cx23885_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_rx_s_min_width (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqenable_rx (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cx23888_ir_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx23888_ir_rx_shutdown(struct v4l2_subdev *sd)
{
	struct cx23888_ir_state *state = to_state(sd);
	struct cx23885_dev *dev = state->dev;

	mutex_lock(&state->rx_params_lock);

	/* Disable or slow down all IR Rx circuits and counters */
	irqenable_rx(dev, 0);
	control_rx_enable(dev, false);
	control_rx_demodulation_enable(dev, false);
	control_rx_s_edge_detection(dev, CNTRL_EDG_NONE);
	filter_rx_s_min_width(dev, 0);
	cx23888_ir_write4(dev, CX23888_IR_RXCLK_REG, RXCLK_RCD);

	state->rx_params.shutdown = true;

	mutex_unlock(&state->rx_params_lock);
	return 0;
}