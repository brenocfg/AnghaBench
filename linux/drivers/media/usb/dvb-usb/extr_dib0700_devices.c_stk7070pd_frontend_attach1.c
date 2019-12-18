#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_2__* fe_adap; TYPE_1__* dev; struct dib0700_adapter_state* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/ * (* init ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
struct dib0700_adapter_state {TYPE_3__ dib7000p_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fe; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dib7000p_attach ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * stk7070pd_dib7000p_config ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stk7070pd_frontend_attach1(struct dvb_usb_adapter *adap)
{
	struct dib0700_adapter_state *state = adap->priv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		return -ENODEV;

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x82, &stk7070pd_dib7000p_config[1]);
	return adap->fe_adap[0].fe == NULL ? -ENODEV : 0;
}