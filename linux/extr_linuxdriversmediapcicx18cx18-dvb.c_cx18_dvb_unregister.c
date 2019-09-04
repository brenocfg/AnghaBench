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
struct dmx_demux {int /*<<< orphan*/  (* remove_frontend ) (struct dmx_demux*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close ) (struct dmx_demux*) ;} ;
struct dvb_demux {struct dmx_demux dmx; } ;
struct dvb_adapter {int dummy; } ;
struct cx18_stream {struct cx18_dvb* dvb; struct cx18* cx; } ;
struct cx18_dvb {int /*<<< orphan*/  fe; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  hw_frontend; int /*<<< orphan*/  mem_frontend; int /*<<< orphan*/  dvbnet; struct dvb_demux demux; struct dvb_adapter dvb_adapter; int /*<<< orphan*/  enabled; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_INFO (char*) ; 
 int /*<<< orphan*/  dvb_dmx_release (struct dvb_demux*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (struct dvb_adapter*) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dmx_demux*) ; 
 int /*<<< orphan*/  stub2 (struct dmx_demux*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct dmx_demux*,int /*<<< orphan*/ *) ; 

void cx18_dvb_unregister(struct cx18_stream *stream)
{
	struct cx18 *cx = stream->cx;
	struct cx18_dvb *dvb = stream->dvb;
	struct dvb_adapter *dvb_adapter;
	struct dvb_demux *dvbdemux;
	struct dmx_demux *dmx;

	CX18_INFO("unregister DVB\n");

	if (dvb == NULL || !dvb->enabled)
		return;

	dvb_adapter = &dvb->dvb_adapter;
	dvbdemux = &dvb->demux;
	dmx = &dvbdemux->dmx;

	dmx->close(dmx);
	dvb_net_release(&dvb->dvbnet);
	dmx->remove_frontend(dmx, &dvb->mem_frontend);
	dmx->remove_frontend(dmx, &dvb->hw_frontend);
	dvb_dmxdev_release(&dvb->dmxdev);
	dvb_dmx_release(dvbdemux);
	dvb_unregister_frontend(dvb->fe);
	dvb_frontend_detach(dvb->fe);
	dvb_unregister_adapter(dvb_adapter);
}