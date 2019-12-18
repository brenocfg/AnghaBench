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
struct ddb_port {TYPE_2__* output; TYPE_1__** input; } ;
struct ddb {int port_num; int /*<<< orphan*/  pdev; struct ddb_port* port; } ;
struct TYPE_4__ {scalar_t__ dma; } ;
struct TYPE_3__ {scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free (int /*<<< orphan*/ ,scalar_t__,int) ; 

void ddb_buffers_free(struct ddb *dev)
{
	int i;
	struct ddb_port *port;

	for (i = 0; i < dev->port_num; i++) {
		port = &dev->port[i];

		if (port->input[0] && port->input[0]->dma)
			dma_free(dev->pdev, port->input[0]->dma, 0);
		if (port->input[1] && port->input[1]->dma)
			dma_free(dev->pdev, port->input[1]->dma, 0);
		if (port->output && port->output->dma)
			dma_free(dev->pdev, port->output->dma, 1);
	}
}