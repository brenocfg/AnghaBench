#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_24__ ;
typedef  struct TYPE_30__   TYPE_21__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;

/* Type definitions */
struct module {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_28__ {int mfe_shared; struct cx231xx* priv; } ;
struct TYPE_32__ {int capabilities; int (* add_frontend ) (TYPE_2__*,TYPE_3__*) ;int (* connect_frontend ) (TYPE_2__*,TYPE_3__*) ;int /*<<< orphan*/  (* remove_frontend ) (TYPE_2__*,TYPE_3__*) ;} ;
struct TYPE_31__ {int filternum; int feednum; TYPE_2__ dmx; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; struct cx231xx_dvb* priv; } ;
struct TYPE_30__ {int filternum; scalar_t__ capabilities; TYPE_2__* demux; } ;
struct TYPE_33__ {int /*<<< orphan*/  source; } ;
struct cx231xx_dvb {TYPE_13__ adapter; TYPE_12__** frontend; TYPE_24__ demux; TYPE_21__ dmxdev; TYPE_3__ fe_hw; TYPE_3__ fe_mem; int /*<<< orphan*/  net; int /*<<< orphan*/  lock; } ;
struct cx231xx {scalar_t__ tuner_type; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  media_dev; } ;
struct TYPE_29__ {void* ts_bus_ctrl; } ;
struct TYPE_27__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_FRONTEND_0 ; 
 int DMX_MEMORY_BASED_FILTERING ; 
 int /*<<< orphan*/  DMX_MEMORY_FE ; 
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 scalar_t__ TUNER_ABSENT ; 
 int /*<<< orphan*/  adapter_nr ; 
 void* cx231xx_dvb_bus_ctrl ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int dvb_create_media_graph (TYPE_13__*,int) ; 
 int dvb_dmx_init (TYPE_24__*) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_24__*) ; 
 int dvb_dmxdev_init (TYPE_21__*,TYPE_13__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (TYPE_21__*) ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_12__*) ; 
 int /*<<< orphan*/  dvb_net_init (TYPE_13__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int dvb_register_adapter (TYPE_13__*,int /*<<< orphan*/ ,struct module*,struct device*,int /*<<< orphan*/ ) ; 
 int dvb_register_frontend (TYPE_13__*,TYPE_12__*) ; 
 int /*<<< orphan*/  dvb_register_media_controller (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (TYPE_13__*) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (TYPE_12__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_feed ; 
 int /*<<< orphan*/  stop_feed ; 
 int stub1 (TYPE_2__*,TYPE_3__*) ; 
 int stub2 (TYPE_2__*,TYPE_3__*) ; 
 int stub3 (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int register_dvb(struct cx231xx_dvb *dvb,
			struct module *module,
			struct cx231xx *dev, struct device *device)
{
	int result;

	mutex_init(&dvb->lock);


	/* register adapter */
	result = dvb_register_adapter(&dvb->adapter, dev->name, module, device,
				      adapter_nr);
	if (result < 0) {
		dev_warn(dev->dev,
		       "%s: dvb_register_adapter failed (errno = %d)\n",
		       dev->name, result);
		goto fail_adapter;
	}
	dvb_register_media_controller(&dvb->adapter, dev->media_dev);

	/* Ensure all frontends negotiate bus access */
	dvb->frontend[0]->ops.ts_bus_ctrl = cx231xx_dvb_bus_ctrl;
	if (dvb->frontend[1])
		dvb->frontend[1]->ops.ts_bus_ctrl = cx231xx_dvb_bus_ctrl;

	dvb->adapter.priv = dev;

	/* register frontend */
	result = dvb_register_frontend(&dvb->adapter, dvb->frontend[0]);
	if (result < 0) {
		dev_warn(dev->dev,
		       "%s: dvb_register_frontend failed (errno = %d)\n",
		       dev->name, result);
		goto fail_frontend0;
	}

	if (dvb->frontend[1]) {
		result = dvb_register_frontend(&dvb->adapter, dvb->frontend[1]);
		if (result < 0) {
			dev_warn(dev->dev,
				 "%s: 2nd dvb_register_frontend failed (errno = %d)\n",
				dev->name, result);
			goto fail_frontend1;
		}

		/* MFE lock */
		dvb->adapter.mfe_shared = 1;
	}

	/* register demux stuff */
	dvb->demux.dmx.capabilities =
	    DMX_TS_FILTERING | DMX_SECTION_FILTERING |
	    DMX_MEMORY_BASED_FILTERING;
	dvb->demux.priv = dvb;
	dvb->demux.filternum = 256;
	dvb->demux.feednum = 256;
	dvb->demux.start_feed = start_feed;
	dvb->demux.stop_feed = stop_feed;

	result = dvb_dmx_init(&dvb->demux);
	if (result < 0) {
		dev_warn(dev->dev,
			 "%s: dvb_dmx_init failed (errno = %d)\n",
		       dev->name, result);
		goto fail_dmx;
	}

	dvb->dmxdev.filternum = 256;
	dvb->dmxdev.demux = &dvb->demux.dmx;
	dvb->dmxdev.capabilities = 0;
	result = dvb_dmxdev_init(&dvb->dmxdev, &dvb->adapter);
	if (result < 0) {
		dev_warn(dev->dev,
			 "%s: dvb_dmxdev_init failed (errno = %d)\n",
			 dev->name, result);
		goto fail_dmxdev;
	}

	dvb->fe_hw.source = DMX_FRONTEND_0;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (result < 0) {
		dev_warn(dev->dev,
		       "%s: add_frontend failed (DMX_FRONTEND_0, errno = %d)\n",
		       dev->name, result);
		goto fail_fe_hw;
	}

	dvb->fe_mem.source = DMX_MEMORY_FE;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	if (result < 0) {
		dev_warn(dev->dev,
			 "%s: add_frontend failed (DMX_MEMORY_FE, errno = %d)\n",
			 dev->name, result);
		goto fail_fe_mem;
	}

	result = dvb->demux.dmx.connect_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (result < 0) {
		dev_warn(dev->dev,
			 "%s: connect_frontend failed (errno = %d)\n",
			 dev->name, result);
		goto fail_fe_conn;
	}

	/* register network adapter */
	dvb_net_init(&dvb->adapter, &dvb->net, &dvb->demux.dmx);
	result = dvb_create_media_graph(&dvb->adapter,
					dev->tuner_type == TUNER_ABSENT);
	if (result < 0)
		goto fail_create_graph;

	return 0;

fail_create_graph:
	dvb_net_release(&dvb->net);
fail_fe_conn:
	dvb->demux.dmx.remove_frontend(&dvb->demux.dmx, &dvb->fe_mem);
fail_fe_mem:
	dvb->demux.dmx.remove_frontend(&dvb->demux.dmx, &dvb->fe_hw);
fail_fe_hw:
	dvb_dmxdev_release(&dvb->dmxdev);
fail_dmxdev:
	dvb_dmx_release(&dvb->demux);
fail_dmx:
	if (dvb->frontend[1])
		dvb_unregister_frontend(dvb->frontend[1]);
	dvb_unregister_frontend(dvb->frontend[0]);
fail_frontend1:
	if (dvb->frontend[1])
		dvb_frontend_detach(dvb->frontend[1]);
fail_frontend0:
	dvb_frontend_detach(dvb->frontend[0]);
	dvb_unregister_adapter(&dvb->adapter);
fail_adapter:
	return result;
}