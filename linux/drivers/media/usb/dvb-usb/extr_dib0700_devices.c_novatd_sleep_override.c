#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_device {struct dib0700_state* priv; } ;
struct dvb_usb_adapter {scalar_t__ id; struct dvb_usb_device* dev; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct dib0700_state {int (* sleep ) (struct dvb_frontend*) ;} ;
struct TYPE_2__ {struct dvb_usb_adapter* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO0 ; 
 int /*<<< orphan*/  GPIO1 ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  dib0700_set_gpio (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int novatd_sleep_override(struct dvb_frontend* fe)
{
	struct dvb_usb_adapter *adap = fe->dvb->priv;
	struct dvb_usb_device *dev = adap->dev;
	struct dib0700_state *state = dev->priv;

	/* turn off LED */
	dib0700_set_gpio(dev, adap->id == 0 ? GPIO1 : GPIO0, GPIO_OUT, 0);

	return state->sleep(fe);
}