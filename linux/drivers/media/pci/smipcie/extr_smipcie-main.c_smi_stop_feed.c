#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smi_port {int users; int /*<<< orphan*/  DMA_MANAGEMENT; int /*<<< orphan*/  tasklet; struct smi_dev* dev; } ;
struct smi_dev {int dummy; } ;
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct dvb_demux {struct smi_port* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  smi_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smi_port_disableInterrupt (struct smi_port*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smi_stop_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	struct smi_port *port = dvbdmx->priv;
	struct smi_dev *dev = port->dev;

	if (--port->users)
		return port->users;

	tasklet_disable(&port->tasklet);
	smi_port_disableInterrupt(port);
	smi_clear(port->DMA_MANAGEMENT, 0x30003);
	return 0;
}