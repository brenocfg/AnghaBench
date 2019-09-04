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
struct ddb_port {struct ddb_dvb* dvb; } ;
struct ddb_dvb {scalar_t__ adap_registered; int /*<<< orphan*/  adap; } ;
struct ddb {struct ddb_port* port; TYPE_2__* link; } ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {int port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dvb_unregister_adapters(struct ddb *dev)
{
	int i;
	struct ddb_port *port;
	struct ddb_dvb *dvb;

	for (i = 0; i < dev->link[0].info->port_num; i++) {
		port = &dev->port[i];

		dvb = &port->dvb[0];
		if (dvb->adap_registered)
			dvb_unregister_adapter(dvb->adap);
		dvb->adap_registered = 0;

		dvb = &port->dvb[1];
		if (dvb->adap_registered)
			dvb_unregister_adapter(dvb->adap);
		dvb->adap_registered = 0;
	}
}