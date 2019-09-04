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
struct dtv_frontend_properties {int frequency; int bandwidth_hz; } ;
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct dtt200u_fe_state {int* data; int /*<<< orphan*/  data_mutex; int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int EINVAL ; 
 int SET_BANDWIDTH ; 
 int SET_RF_FREQ ; 
 int dvb_usb_generic_write (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dtt200u_fe_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *fep = &fe->dtv_property_cache;
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	int ret;
	u16 freq = fep->frequency / 250000;

	mutex_lock(&state->data_mutex);
	state->data[0] = SET_BANDWIDTH;
	switch (fep->bandwidth_hz) {
	case 8000000:
		state->data[1] = 8;
		break;
	case 7000000:
		state->data[1] = 7;
		break;
	case 6000000:
		state->data[1] = 6;
		break;
	default:
		ret = -EINVAL;
		goto ret;
	}

	ret = dvb_usb_generic_write(state->d, state->data, 2);
	if (ret < 0)
		goto ret;

	state->data[0] = SET_RF_FREQ;
	state->data[1] = freq & 0xff;
	state->data[2] = (freq >> 8) & 0xff;
	ret = dvb_usb_generic_write(state->d, state->data, 3);
	if (ret < 0)
		goto ret;

ret:
	mutex_unlock(&state->data_mutex);
	return ret;
}