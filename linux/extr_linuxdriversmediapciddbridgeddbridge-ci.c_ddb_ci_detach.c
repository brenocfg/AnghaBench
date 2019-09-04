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
struct ddb_port {TYPE_2__* en; scalar_t__ en_freedata; TYPE_1__* dvb; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** i2c_client; scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_ca_en50221_release (TYPE_2__*) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void ddb_ci_detach(struct ddb_port *port)
{
	if (port->dvb[0].dev)
		dvb_unregister_device(port->dvb[0].dev);
	if (port->en) {
		dvb_ca_en50221_release(port->en);

		dvb_module_release(port->dvb[0].i2c_client[0]);
		port->dvb[0].i2c_client[0] = NULL;

		/* free alloc'ed memory if needed */
		if (port->en_freedata)
			kfree(port->en->data);

		port->en = NULL;
	}
}