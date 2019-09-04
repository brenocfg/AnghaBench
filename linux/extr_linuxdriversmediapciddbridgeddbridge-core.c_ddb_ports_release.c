#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ddb_port {TYPE_4__* output; TYPE_2__** input; } ;
struct ddb {int port_num; struct ddb_port* port; } ;
struct TYPE_8__ {TYPE_3__* dma; } ;
struct TYPE_7__ {int /*<<< orphan*/  work; } ;
struct TYPE_6__ {TYPE_1__* dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

void ddb_ports_release(struct ddb *dev)
{
	int i;
	struct ddb_port *port;

	for (i = 0; i < dev->port_num; i++) {
		port = &dev->port[i];
		if (port->input[0] && port->input[0]->dma)
			cancel_work_sync(&port->input[0]->dma->work);
		if (port->input[1] && port->input[1]->dma)
			cancel_work_sync(&port->input[1]->dma->work);
		if (port->output && port->output->dma)
			cancel_work_sync(&port->output->dma->work);
	}
}