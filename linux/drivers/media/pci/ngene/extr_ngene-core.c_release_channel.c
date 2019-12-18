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
struct ngene_channel {int has_demux; int has_adapter; size_t number; struct dvb_demux demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  mem_frontend; int /*<<< orphan*/  hw_frontend; int /*<<< orphan*/  dvbnet; int /*<<< orphan*/ * fe; int /*<<< orphan*/ ** i2c_client; scalar_t__ i2c_client_fe; int /*<<< orphan*/ * fe2; int /*<<< orphan*/ * ci_dev; int /*<<< orphan*/  demux_tasklet; scalar_t__ running; struct ngene* dev; } ;
struct ngene {int /*<<< orphan*/ * adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (struct dvb_demux*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_transfer (struct ngene_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_channel(struct ngene_channel *chan)
{
	struct dvb_demux *dvbdemux = &chan->demux;
	struct ngene *dev = chan->dev;

	if (chan->running)
		set_transfer(chan, 0);

	tasklet_kill(&chan->demux_tasklet);

	if (chan->ci_dev) {
		dvb_unregister_device(chan->ci_dev);
		chan->ci_dev = NULL;
	}

	if (chan->fe2)
		dvb_unregister_frontend(chan->fe2);

	if (chan->fe) {
		dvb_unregister_frontend(chan->fe);

		/* release I2C client (tuner) if needed */
		if (chan->i2c_client_fe) {
			dvb_module_release(chan->i2c_client[0]);
			chan->i2c_client[0] = NULL;
		}

		dvb_frontend_detach(chan->fe);
		chan->fe = NULL;
	}

	if (chan->has_demux) {
		dvb_net_release(&chan->dvbnet);
		dvbdemux->dmx.close(&dvbdemux->dmx);
		dvbdemux->dmx.remove_frontend(&dvbdemux->dmx,
					      &chan->hw_frontend);
		dvbdemux->dmx.remove_frontend(&dvbdemux->dmx,
					      &chan->mem_frontend);
		dvb_dmxdev_release(&chan->dmxdev);
		dvb_dmx_release(&chan->demux);
		chan->has_demux = false;
	}

	if (chan->has_adapter) {
		dvb_unregister_adapter(&dev->adapter[chan->number]);
		chan->has_adapter = false;
	}
}