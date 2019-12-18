#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close ) (TYPE_1__*) ;} ;
struct dvb_demux {TYPE_1__ dmx; } ;
struct av7110 {int /*<<< orphan*/  osd_dev; int /*<<< orphan*/ * fe; struct dvb_demux demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  mem_frontend; int /*<<< orphan*/  hw_frontend; int /*<<< orphan*/  dvb_net; struct dvb_demux demux1; int /*<<< orphan*/  dmxdev1; int /*<<< orphan*/  dvb_net1; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  av7110_av_unregister (struct av7110*) ; 
 int /*<<< orphan*/  av7110_ca_unregister (struct av7110*) ; 
 scalar_t__ budgetpatch ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int /*<<< orphan*/  dvb_dmx_release (struct dvb_demux*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dvb_unregister(struct av7110 *av7110)
{
	struct dvb_demux *dvbdemux = &av7110->demux;
	struct dvb_demux *dvbdemux1 = &av7110->demux1;

	dprintk(4, "%p\n", av7110);

	if (!av7110->registered)
		return;

	if (budgetpatch) {
		dvb_net_release(&av7110->dvb_net1);
		dvbdemux->dmx.close(&dvbdemux1->dmx);
		dvb_dmxdev_release(&av7110->dmxdev1);
		dvb_dmx_release(&av7110->demux1);
	}

	dvb_net_release(&av7110->dvb_net);

	dvbdemux->dmx.close(&dvbdemux->dmx);
	dvbdemux->dmx.remove_frontend(&dvbdemux->dmx, &av7110->hw_frontend);
	dvbdemux->dmx.remove_frontend(&dvbdemux->dmx, &av7110->mem_frontend);

	dvb_dmxdev_release(&av7110->dmxdev);
	dvb_dmx_release(&av7110->demux);

	if (av7110->fe != NULL) {
		dvb_unregister_frontend(av7110->fe);
		dvb_frontend_detach(av7110->fe);
	}
	dvb_unregister_device(av7110->osd_dev);
	av7110_av_unregister(av7110);
	av7110_ca_unregister(av7110);
}