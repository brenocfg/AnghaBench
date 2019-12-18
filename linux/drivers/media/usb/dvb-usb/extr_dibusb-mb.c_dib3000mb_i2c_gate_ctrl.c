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
struct dvb_usb_adapter {struct dibusb_state* priv; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct TYPE_4__ {int (* tuner_pass_ctrl ) (struct dvb_frontend*,int,int /*<<< orphan*/ ) ;} ;
struct dibusb_state {int /*<<< orphan*/  tuner_addr; TYPE_2__ ops; } ;
struct TYPE_3__ {struct dvb_usb_adapter* priv; } ;

/* Variables and functions */
 int stub1 (struct dvb_frontend*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib3000mb_i2c_gate_ctrl(struct dvb_frontend* fe, int enable)
{
	struct dvb_usb_adapter *adap = fe->dvb->priv;
	struct dibusb_state *st = adap->priv;

	return st->ops.tuner_pass_ctrl(fe, enable, st->tuner_addr);
}