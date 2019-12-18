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
struct v4l2_subdev {int dummy; } ;
struct cx25840_state {int /*<<< orphan*/ * ir_state; } ;
struct cx25840_ir_state {int /*<<< orphan*/  rx_kfifo; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cx25840_ir_rx_shutdown (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  cx25840_ir_tx_shutdown (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 struct cx25840_ir_state* to_ir_state (struct v4l2_subdev*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 

int cx25840_ir_remove(struct v4l2_subdev *sd)
{
	struct cx25840_state *state = to_state(sd);
	struct cx25840_ir_state *ir_state = to_ir_state(sd);

	if (ir_state == NULL)
		return -ENODEV;

	cx25840_ir_rx_shutdown(sd);
	cx25840_ir_tx_shutdown(sd);

	kfifo_free(&ir_state->rx_kfifo);
	state->ir_state = NULL;
	return 0;
}