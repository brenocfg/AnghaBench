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
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; } ;
struct dtt200u_fe_state {int /*<<< orphan*/  data_mutex; int /*<<< orphan*/ * data; int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_INIT ; 
 int dvb_usb_generic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dtt200u_fe_init(struct dvb_frontend* fe)
{
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	int ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = SET_INIT;

	ret = dvb_usb_generic_write(state->d, state->data, 1);
	mutex_unlock(&state->data_mutex);

	return ret;
}