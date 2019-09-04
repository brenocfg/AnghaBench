#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_2__* fe_adap; struct dib0700_adapter_state* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_gpio ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;
struct dib0700_adapter_state {TYPE_1__ dib7000p_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int EINVAL ; 
 int XC4000_TUNER_RESET ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib0700_xc4000_tuner_callback(void *priv, int component,
					 int command, int arg)
{
	struct dvb_usb_adapter *adap = priv;
	struct dib0700_adapter_state *state = adap->priv;

	if (command == XC4000_TUNER_RESET) {
		/* Reset the tuner */
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 0);
		msleep(10);
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);
	} else {
		err("xc4000: unknown tuner callback command: %d\n", command);
		return -EINVAL;
	}

	return 0;
}