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
struct mantis_pci {scalar_t__ feeds; int /*<<< orphan*/  tasklet; } ;
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct TYPE_2__ {int /*<<< orphan*/  frontend; } ;
struct dvb_demux {TYPE_1__ dmx; struct mantis_pci* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mantis_dma_stop (struct mantis_pci*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mantis_dvb_stop_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	struct mantis_pci *mantis = dvbdmx->priv;

	dprintk(MANTIS_DEBUG, 1, "Mantis DVB Stop feed");
	if (!dvbdmx->dmx.frontend) {
		dprintk(MANTIS_DEBUG, 1, "no frontend ?");
		return -EINVAL;
	}

	mantis->feeds--;
	if (mantis->feeds == 0) {
		dprintk(MANTIS_DEBUG, 1, "mantis stop feed and dma");
		tasklet_disable(&mantis->tasklet);
		mantis_dma_stop(mantis);
	}

	return 0;
}