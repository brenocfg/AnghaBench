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
struct dvb_usb_device {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
struct dvb_frontend {struct af9005_fe_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct af9005_fe_state {struct dvb_frontend frontend; scalar_t__ opened; struct dvb_usb_device* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  af9005_fe_ops ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 struct af9005_fe_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend *af9005_fe_attach(struct dvb_usb_device *d)
{
	struct af9005_fe_state *state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct af9005_fe_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	deb_info("attaching frontend af9005\n");

	state->d = d;
	state->opened = 0;

	memcpy(&state->frontend.ops, &af9005_fe_ops,
	       sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	return &state->frontend;
      error:
	return NULL;
}