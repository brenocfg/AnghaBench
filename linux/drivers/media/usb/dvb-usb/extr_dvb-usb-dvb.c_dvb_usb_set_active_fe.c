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
struct TYPE_4__ {int (* frontend_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_usb_adapter {int /*<<< orphan*/  active_fe; TYPE_2__ props; } ;
struct dvb_frontend {int /*<<< orphan*/  id; TYPE_1__* dvb; } ;
struct TYPE_3__ {struct dvb_usb_adapter* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*) ; 
 int stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int dvb_usb_set_active_fe(struct dvb_frontend *fe, int onoff)
{
	struct dvb_usb_adapter *adap = fe->dvb->priv;

	int ret = (adap->props.frontend_ctrl) ?
		adap->props.frontend_ctrl(fe, onoff) : 0;

	if (ret < 0) {
		err("frontend_ctrl request failed");
		return ret;
	}
	if (onoff)
		adap->active_fe = fe->id;

	return 0;
}