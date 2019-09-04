#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_26__ ;
typedef  struct TYPE_30__   TYPE_23__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_16__ ;

/* Type definitions */
struct TYPE_28__ {struct mantis_pci* priv; } ;
struct TYPE_33__ {int capabilities; int (* add_frontend ) (TYPE_3__*,TYPE_4__*) ;int (* connect_frontend ) (TYPE_3__*,TYPE_4__*) ;int /*<<< orphan*/  (* remove_frontend ) (TYPE_3__*,TYPE_4__*) ;} ;
struct TYPE_31__ {int filternum; int feednum; TYPE_3__ dmx; int /*<<< orphan*/ * write_to_decoder; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; struct mantis_pci* priv; } ;
struct TYPE_30__ {int filternum; scalar_t__ capabilities; TYPE_3__* demux; } ;
struct TYPE_34__ {int /*<<< orphan*/  source; } ;
struct mantis_pci {TYPE_16__ dvb_adapter; TYPE_26__ demux; TYPE_23__ dmxdev; TYPE_4__ fe_hw; TYPE_4__ fe_mem; TYPE_7__* fe; int /*<<< orphan*/  dvbnet; int /*<<< orphan*/  tasklet; struct mantis_hwconfig* hwconfig; TYPE_1__* pdev; } ;
struct mantis_hwconfig {int (* frontend_init ) (struct mantis_pci*,TYPE_7__*) ;} ;
struct TYPE_32__ {int /*<<< orphan*/  (* release ) (TYPE_7__*) ;} ;
struct TYPE_35__ {TYPE_2__ ops; } ;
struct TYPE_29__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_FRONTEND_0 ; 
 int DMX_MEMORY_BASED_FILTERING ; 
 int /*<<< orphan*/  DMX_MEMORY_FE ; 
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 int dvb_dmx_init (TYPE_26__*) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_26__*) ; 
 int dvb_dmxdev_init (TYPE_23__*,TYPE_16__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (TYPE_23__*) ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_7__*) ; 
 int /*<<< orphan*/  dvb_net_init (TYPE_16__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int dvb_register_adapter (TYPE_16__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dvb_register_frontend (TYPE_16__*,TYPE_7__*) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (TYPE_16__*) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (TYPE_7__*) ; 
 int /*<<< orphan*/  mantis_dma_xfer ; 
 int /*<<< orphan*/  mantis_dvb_start_feed ; 
 int /*<<< orphan*/  mantis_dvb_stop_feed ; 
 int stub1 (TYPE_3__*,TYPE_4__*) ; 
 int stub2 (TYPE_3__*,TYPE_4__*) ; 
 int stub3 (TYPE_3__*,TYPE_4__*) ; 
 int stub4 (struct mantis_pci*,TYPE_7__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

int mantis_dvb_init(struct mantis_pci *mantis)
{
	struct mantis_hwconfig *config = mantis->hwconfig;
	int result = -1;

	dprintk(MANTIS_DEBUG, 1, "dvb_register_adapter");

	result = dvb_register_adapter(&mantis->dvb_adapter,
				      "Mantis DVB adapter",
				      THIS_MODULE,
				      &mantis->pdev->dev,
				      adapter_nr);

	if (result < 0) {

		dprintk(MANTIS_ERROR, 1, "Error registering adapter");
		return -ENODEV;
	}

	mantis->dvb_adapter.priv	= mantis;
	mantis->demux.dmx.capabilities	= DMX_TS_FILTERING	|
					 DMX_SECTION_FILTERING	|
					 DMX_MEMORY_BASED_FILTERING;

	mantis->demux.priv		= mantis;
	mantis->demux.filternum		= 256;
	mantis->demux.feednum		= 256;
	mantis->demux.start_feed	= mantis_dvb_start_feed;
	mantis->demux.stop_feed		= mantis_dvb_stop_feed;
	mantis->demux.write_to_decoder	= NULL;

	dprintk(MANTIS_DEBUG, 1, "dvb_dmx_init");
	result = dvb_dmx_init(&mantis->demux);
	if (result < 0) {
		dprintk(MANTIS_ERROR, 1, "dvb_dmx_init failed, ERROR=%d", result);

		goto err0;
	}

	mantis->dmxdev.filternum	= 256;
	mantis->dmxdev.demux		= &mantis->demux.dmx;
	mantis->dmxdev.capabilities	= 0;
	dprintk(MANTIS_DEBUG, 1, "dvb_dmxdev_init");

	result = dvb_dmxdev_init(&mantis->dmxdev, &mantis->dvb_adapter);
	if (result < 0) {

		dprintk(MANTIS_ERROR, 1, "dvb_dmxdev_init failed, ERROR=%d", result);
		goto err1;
	}

	mantis->fe_hw.source		= DMX_FRONTEND_0;
	result = mantis->demux.dmx.add_frontend(&mantis->demux.dmx, &mantis->fe_hw);
	if (result < 0) {

		dprintk(MANTIS_ERROR, 1, "dvb_dmx_init failed, ERROR=%d", result);
		goto err2;
	}

	mantis->fe_mem.source		= DMX_MEMORY_FE;
	result = mantis->demux.dmx.add_frontend(&mantis->demux.dmx, &mantis->fe_mem);
	if (result < 0) {
		dprintk(MANTIS_ERROR, 1, "dvb_dmx_init failed, ERROR=%d", result);
		goto err3;
	}

	result = mantis->demux.dmx.connect_frontend(&mantis->demux.dmx, &mantis->fe_hw);
	if (result < 0) {
		dprintk(MANTIS_ERROR, 1, "dvb_dmx_init failed, ERROR=%d", result);
		goto err4;
	}

	dvb_net_init(&mantis->dvb_adapter, &mantis->dvbnet, &mantis->demux.dmx);
	tasklet_init(&mantis->tasklet, mantis_dma_xfer, (unsigned long) mantis);
	tasklet_disable(&mantis->tasklet);
	if (mantis->hwconfig) {
		result = config->frontend_init(mantis, mantis->fe);
		if (result < 0) {
			dprintk(MANTIS_ERROR, 1, "!!! NO Frontends found !!!");
			goto err5;
		} else {
			if (mantis->fe == NULL) {
				result = -ENOMEM;
				dprintk(MANTIS_ERROR, 1, "FE <NULL>");
				goto err5;
			}
			result = dvb_register_frontend(&mantis->dvb_adapter, mantis->fe);
			if (result) {
				dprintk(MANTIS_ERROR, 1, "ERROR: Frontend registration failed");

				if (mantis->fe->ops.release)
					mantis->fe->ops.release(mantis->fe);

				mantis->fe = NULL;
				goto err5;
			}
		}
	}

	return 0;

	/* Error conditions ..	*/
err5:
	tasklet_kill(&mantis->tasklet);
	dvb_net_release(&mantis->dvbnet);
	if (mantis->fe) {
		dvb_unregister_frontend(mantis->fe);
		dvb_frontend_detach(mantis->fe);
	}
err4:
	mantis->demux.dmx.remove_frontend(&mantis->demux.dmx, &mantis->fe_mem);

err3:
	mantis->demux.dmx.remove_frontend(&mantis->demux.dmx, &mantis->fe_hw);

err2:
	dvb_dmxdev_release(&mantis->dmxdev);

err1:
	dvb_dmx_release(&mantis->demux);

err0:
	dvb_unregister_adapter(&mantis->dvb_adapter);

	return result;
}