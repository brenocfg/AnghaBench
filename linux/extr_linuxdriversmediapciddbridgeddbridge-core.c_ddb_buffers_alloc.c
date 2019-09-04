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
struct ddb_port {int class; TYPE_2__* output; TYPE_1__** input; } ;
struct ddb {int port_num; int /*<<< orphan*/  pdev; struct ddb_port* port; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
#define  DDB_PORT_CI 130 
#define  DDB_PORT_LOOP 129 
#define  DDB_PORT_TUNER 128 
 int /*<<< orphan*/  ddb_set_dma_tables (struct ddb*) ; 
 int /*<<< orphan*/  dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ddb_buffers_alloc(struct ddb *dev)
{
	int i;
	struct ddb_port *port;

	for (i = 0; i < dev->port_num; i++) {
		port = &dev->port[i];
		switch (port->class) {
		case DDB_PORT_TUNER:
			if (port->input[0]->dma)
				if (dma_alloc(dev->pdev, port->input[0]->dma, 0)
					< 0)
					return -1;
			if (port->input[1]->dma)
				if (dma_alloc(dev->pdev, port->input[1]->dma, 0)
					< 0)
					return -1;
			break;
		case DDB_PORT_CI:
		case DDB_PORT_LOOP:
			if (port->input[0]->dma)
				if (dma_alloc(dev->pdev, port->input[0]->dma, 0)
					< 0)
					return -1;
			if (port->output->dma)
				if (dma_alloc(dev->pdev, port->output->dma, 1)
					< 0)
					return -1;
			break;
		default:
			break;
		}
	}
	ddb_set_dma_tables(dev);
	return 0;
}