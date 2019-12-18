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
struct dvb_usb_adapter {int num_frontends_initialized; TYPE_1__* fe_adap; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 

int dvb_usb_adapter_frontend_exit(struct dvb_usb_adapter *adap)
{
	int i = adap->num_frontends_initialized - 1;

	/* unregister all given adapter frontends */
	for (; i >= 0; i--) {
		if (adap->fe_adap[i].fe != NULL) {
			dvb_unregister_frontend(adap->fe_adap[i].fe);
			dvb_frontend_detach(adap->fe_adap[i].fe);
		}
	}
	adap->num_frontends_initialized = 0;

	return 0;
}