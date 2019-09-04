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
struct TYPE_4__ {int (* connect_frontend ) (TYPE_1__*,struct dmx_frontend*) ;int /*<<< orphan*/  (* add_frontend ) (TYPE_1__*,struct dmx_frontend*) ;} ;
struct dvb_demux {TYPE_1__ dmx; } ;
struct dvb_adapter {int dummy; } ;
struct dmxdev {int filternum; scalar_t__ capabilities; TYPE_1__* demux; } ;
struct dmx_frontend {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_FRONTEND_0 ; 
 int /*<<< orphan*/  DMX_MEMORY_FE ; 
 int dvb_dmxdev_init (struct dmxdev*,struct dvb_adapter*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct dmx_frontend*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,struct dmx_frontend*) ; 
 int stub3 (TYPE_1__*,struct dmx_frontend*) ; 

__attribute__((used)) static int my_dvb_dmxdev_ts_card_init(struct dmxdev *dmxdev,
			       struct dvb_demux *dvbdemux,
			       struct dmx_frontend *hw_frontend,
			       struct dmx_frontend *mem_frontend,
			       struct dvb_adapter *dvb_adapter)
{
	int ret;

	dmxdev->filternum = 256;
	dmxdev->demux = &dvbdemux->dmx;
	dmxdev->capabilities = 0;
	ret = dvb_dmxdev_init(dmxdev, dvb_adapter);
	if (ret < 0)
		return ret;

	hw_frontend->source = DMX_FRONTEND_0;
	dvbdemux->dmx.add_frontend(&dvbdemux->dmx, hw_frontend);
	mem_frontend->source = DMX_MEMORY_FE;
	dvbdemux->dmx.add_frontend(&dvbdemux->dmx, mem_frontend);
	return dvbdemux->dmx.connect_frontend(&dvbdemux->dmx, hw_frontend);
}