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
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; } ;
struct dtt200u_fe_state {int* data; int /*<<< orphan*/  data_mutex; int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int GET_SNR ; 
 int dvb_usb_generic_rw (int /*<<< orphan*/ ,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dtt200u_fe_read_snr(struct dvb_frontend* fe, u16 *snr)
{
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	int ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = GET_SNR;

	ret = dvb_usb_generic_rw(state->d, state->data, 1, state->data, 1, 0);
	if (ret >= 0)
		*snr = ~((state->data[0] << 8) | state->data[0]);

	mutex_unlock(&state->data_mutex);
	return ret;
}