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
typedef  int u16 ;
struct dvb_usb_adapter {struct dib0700_adapter_state* priv; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_agc1_min ) (struct dvb_frontend*,int) ;int /*<<< orphan*/  (* set_gpio ) (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ;} ;
struct dib0700_adapter_state {TYPE_2__ dib7000p_ops; } ;
struct TYPE_3__ {struct dvb_usb_adapter* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_info (char*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int tfe7790p_update_lna(struct dvb_frontend *fe, u16 agc_global)
{
	struct dvb_usb_adapter *adap = fe->dvb->priv;
	struct dib0700_adapter_state *state = adap->priv;

	deb_info("update LNA: agc global=%i", agc_global);

	if (agc_global < 25000) {
		state->dib7000p_ops.set_gpio(fe, 8, 0, 0);
		state->dib7000p_ops.set_agc1_min(fe, 0);
	} else {
		state->dib7000p_ops.set_gpio(fe, 8, 0, 1);
		state->dib7000p_ops.set_agc1_min(fe, 32768);
	}

	return 0;
}