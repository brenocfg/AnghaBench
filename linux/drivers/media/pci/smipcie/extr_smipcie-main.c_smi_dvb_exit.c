#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close ) (TYPE_1__*) ;} ;
struct dvb_demux {TYPE_1__ dmx; } ;
struct smi_port {int /*<<< orphan*/  dvb_adapter; struct dvb_demux demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  mem_frontend; int /*<<< orphan*/  hw_frontend; int /*<<< orphan*/  dvbnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (struct dvb_demux*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smi_dvb_exit(struct smi_port *port)
{
	struct dvb_demux *dvbdemux = &port->demux;

	dvb_net_release(&port->dvbnet);

	dvbdemux->dmx.close(&dvbdemux->dmx);
	dvbdemux->dmx.remove_frontend(&dvbdemux->dmx, &port->hw_frontend);
	dvbdemux->dmx.remove_frontend(&dvbdemux->dmx, &port->mem_frontend);
	dvb_dmxdev_release(&port->dmxdev);
	dvb_dmx_release(&port->demux);

	dvb_unregister_adapter(&port->dvb_adapter);
}