#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* remove_frontend ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct dvb_demux {TYPE_2__ dmx; } ;
struct ddb_input {int nr; TYPE_1__* port; } ;
struct ddb_dvb {int attached; struct dvb_demux demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  mem_frontend; int /*<<< orphan*/  hw_frontend; int /*<<< orphan*/  dvbnet; int /*<<< orphan*/ * fe2; int /*<<< orphan*/ * fe; int /*<<< orphan*/ ** i2c_client; } ;
struct TYPE_4__ {struct ddb_dvb* dvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (struct dvb_demux*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dvb_input_detach(struct ddb_input *input)
{
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct dvb_demux *dvbdemux = &dvb->demux;

	switch (dvb->attached) {
	case 0x31:
		if (dvb->fe2)
			dvb_unregister_frontend(dvb->fe2);
		if (dvb->fe)
			dvb_unregister_frontend(dvb->fe);
		/* fallthrough */
	case 0x30:
		dvb_module_release(dvb->i2c_client[0]);
		dvb->i2c_client[0] = NULL;

		if (dvb->fe2)
			dvb_frontend_detach(dvb->fe2);
		if (dvb->fe)
			dvb_frontend_detach(dvb->fe);
		dvb->fe = NULL;
		dvb->fe2 = NULL;
		/* fallthrough */
	case 0x20:
		dvb_net_release(&dvb->dvbnet);
		/* fallthrough */
	case 0x12:
		dvbdemux->dmx.remove_frontend(&dvbdemux->dmx,
					      &dvb->hw_frontend);
		dvbdemux->dmx.remove_frontend(&dvbdemux->dmx,
					      &dvb->mem_frontend);
		/* fallthrough */
	case 0x11:
		dvb_dmxdev_release(&dvb->dmxdev);
		/* fallthrough */
	case 0x10:
		dvb_dmx_release(&dvb->demux);
		/* fallthrough */
	case 0x01:
		break;
	}
	dvb->attached = 0x00;
}