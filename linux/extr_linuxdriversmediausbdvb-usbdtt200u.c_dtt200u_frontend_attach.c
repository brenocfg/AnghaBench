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
struct dvb_usb_adapter {int /*<<< orphan*/  dev; TYPE_1__* fe_adap; } ;
struct TYPE_2__ {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dtt200u_fe_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtt200u_frontend_attach(struct dvb_usb_adapter *adap)
{
	adap->fe_adap[0].fe = dtt200u_fe_attach(adap->dev);
	return 0;
}