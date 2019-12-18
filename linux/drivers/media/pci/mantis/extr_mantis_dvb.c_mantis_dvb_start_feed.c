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
struct mantis_pci {int feeds; int /*<<< orphan*/  tasklet; } ;
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct TYPE_2__ {int /*<<< orphan*/  frontend; } ;
struct dvb_demux {TYPE_1__ dmx; struct mantis_pci* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  mantis_dma_start (struct mantis_pci*) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mantis_dvb_start_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	struct mantis_pci *mantis = dvbdmx->priv;

	dprintk(MANTIS_DEBUG, 1, "Mantis DVB Start feed");
	if (!dvbdmx->dmx.frontend) {
		dprintk(MANTIS_DEBUG, 1, "no frontend ?");
		return -EINVAL;
	}

	mantis->feeds++;
	dprintk(MANTIS_DEBUG, 1, "mantis start feed, feeds=%d",	mantis->feeds);

	if (mantis->feeds == 1)	 {
		dprintk(MANTIS_DEBUG, 1, "mantis start feed & dma");
		mantis_dma_start(mantis);
		tasklet_enable(&mantis->tasklet);
	}

	return mantis->feeds;
}