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
struct dvbsky_state {int /*<<< orphan*/  i2c_client_ci; int /*<<< orphan*/  i2c_client_demod; int /*<<< orphan*/  i2c_client_tuner; } ;
struct dvb_usb_device {struct dvb_usb_adapter* adapter; } ;
struct dvb_usb_adapter {int /*<<< orphan*/ ** fe; } ;

/* Variables and functions */
 struct dvbsky_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dvbsky_exit(struct dvb_usb_device *d)
{
	struct dvbsky_state *state = d_to_priv(d);
	struct dvb_usb_adapter *adap = &d->adapter[0];

	dvb_module_release(state->i2c_client_tuner);
	dvb_module_release(state->i2c_client_demod);
	dvb_module_release(state->i2c_client_ci);

	adap->fe[0] = NULL;
}