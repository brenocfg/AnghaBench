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
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct dtt200u_fe_state {struct dvb_frontend frontend; int /*<<< orphan*/  data_mutex; struct dvb_usb_device* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/  dtt200u_fe_ops ; 
 struct dtt200u_fe_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct dvb_frontend* dtt200u_fe_attach(struct dvb_usb_device *d)
{
	struct dtt200u_fe_state* state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct dtt200u_fe_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	deb_info("attaching frontend dtt200u\n");

	state->d = d;
	mutex_init(&state->data_mutex);

	memcpy(&state->frontend.ops,&dtt200u_fe_ops,sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	return &state->frontend;
error:
	return NULL;
}