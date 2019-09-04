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
struct dvb_usb_adapter {TYPE_2__* dev; TYPE_1__* fe_adap; } ;
struct TYPE_6__ {int /*<<< orphan*/  callback; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_4__ {TYPE_3__* fe; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dib0700_xc5000_tuner_callback ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5h1411_xc5000_tunerconfig ; 
 int /*<<< orphan*/  xc5000_attach ; 

__attribute__((used)) static int xc5000_tuner_attach(struct dvb_usb_adapter *adap)
{
	/* FIXME: generalize & move to common area */
	adap->fe_adap[0].fe->callback = dib0700_xc5000_tuner_callback;

	return dvb_attach(xc5000_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap,
			  &s5h1411_xc5000_tunerconfig)
		== NULL ? -ENODEV : 0;
}