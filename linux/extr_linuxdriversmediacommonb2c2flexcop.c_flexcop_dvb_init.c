#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;
typedef  struct TYPE_22__   TYPE_16__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
struct TYPE_21__ {struct flexcop_device* priv; } ;
struct TYPE_24__ {int capabilities; int (* add_frontend ) (TYPE_1__*,TYPE_2__*) ;int (* connect_frontend ) (TYPE_1__*,TYPE_2__*) ;int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,TYPE_2__*) ;int /*<<< orphan*/  (* disconnect_frontend ) (TYPE_1__*) ;} ;
struct TYPE_23__ {TYPE_1__ dmx; int /*<<< orphan*/  feednum; int /*<<< orphan*/ * write_to_decoder; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; int /*<<< orphan*/  filternum; struct flexcop_device* priv; } ;
struct TYPE_22__ {scalar_t__ capabilities; TYPE_1__* demux; int /*<<< orphan*/  filternum; } ;
struct TYPE_25__ {int /*<<< orphan*/  source; } ;
struct flexcop_device {TYPE_12__ dvb_adapter; TYPE_19__ demux; TYPE_16__ dmxdev; TYPE_2__ hw_frontend; TYPE_2__ mem_frontend; int /*<<< orphan*/  init_state; int /*<<< orphan*/  dvbnet; int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_FRONTEND_0 ; 
 int DMX_MEMORY_BASED_FILTERING ; 
 int /*<<< orphan*/  DMX_MEMORY_FE ; 
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 int /*<<< orphan*/  FC_MAX_FEED ; 
 int /*<<< orphan*/  FC_STATE_DVB_INIT ; 
 int /*<<< orphan*/  adapter_nr ; 
 int dvb_dmx_init (TYPE_19__*) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_19__*) ; 
 int dvb_dmxdev_init (TYPE_16__*,TYPE_12__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (TYPE_16__*) ; 
 int dvb_net_init (TYPE_12__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dvb_register_adapter (TYPE_12__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (TYPE_12__*) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  flexcop_dvb_start_feed ; 
 int /*<<< orphan*/  flexcop_dvb_stop_feed ; 
 int stub1 (TYPE_1__*,TYPE_2__*) ; 
 int stub2 (TYPE_1__*,TYPE_2__*) ; 
 int stub3 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int flexcop_dvb_init(struct flexcop_device *fc)
{
	int ret = dvb_register_adapter(&fc->dvb_adapter,
			"FlexCop Digital TV device", fc->owner,
			fc->dev, adapter_nr);
	if (ret < 0) {
		err("error registering DVB adapter");
		return ret;
	}
	fc->dvb_adapter.priv = fc;

	fc->demux.dmx.capabilities = (DMX_TS_FILTERING | DMX_SECTION_FILTERING
			| DMX_MEMORY_BASED_FILTERING);
	fc->demux.priv = fc;
	fc->demux.filternum = fc->demux.feednum = FC_MAX_FEED;
	fc->demux.start_feed = flexcop_dvb_start_feed;
	fc->demux.stop_feed = flexcop_dvb_stop_feed;
	fc->demux.write_to_decoder = NULL;

	ret = dvb_dmx_init(&fc->demux);
	if (ret < 0) {
		err("dvb_dmx failed: error %d", ret);
		goto err_dmx;
	}

	fc->hw_frontend.source = DMX_FRONTEND_0;

	fc->dmxdev.filternum = fc->demux.feednum;
	fc->dmxdev.demux = &fc->demux.dmx;
	fc->dmxdev.capabilities = 0;
	ret = dvb_dmxdev_init(&fc->dmxdev, &fc->dvb_adapter);
	if (ret < 0) {
		err("dvb_dmxdev_init failed: error %d", ret);
		goto err_dmx_dev;
	}

	ret = fc->demux.dmx.add_frontend(&fc->demux.dmx, &fc->hw_frontend);
	if (ret < 0) {
		err("adding hw_frontend to dmx failed: error %d", ret);
		goto err_dmx_add_hw_frontend;
	}

	fc->mem_frontend.source = DMX_MEMORY_FE;
	ret = fc->demux.dmx.add_frontend(&fc->demux.dmx, &fc->mem_frontend);
	if (ret < 0) {
		err("adding mem_frontend to dmx failed: error %d", ret);
		goto err_dmx_add_mem_frontend;
	}

	ret = fc->demux.dmx.connect_frontend(&fc->demux.dmx, &fc->hw_frontend);
	if (ret < 0) {
		err("connect frontend failed: error %d", ret);
		goto err_connect_frontend;
	}

	ret = dvb_net_init(&fc->dvb_adapter, &fc->dvbnet, &fc->demux.dmx);
	if (ret < 0) {
		err("dvb_net_init failed: error %d", ret);
		goto err_net;
	}

	fc->init_state |= FC_STATE_DVB_INIT;
	return 0;

err_net:
	fc->demux.dmx.disconnect_frontend(&fc->demux.dmx);
err_connect_frontend:
	fc->demux.dmx.remove_frontend(&fc->demux.dmx, &fc->mem_frontend);
err_dmx_add_mem_frontend:
	fc->demux.dmx.remove_frontend(&fc->demux.dmx, &fc->hw_frontend);
err_dmx_add_hw_frontend:
	dvb_dmxdev_release(&fc->dmxdev);
err_dmx_dev:
	dvb_dmx_release(&fc->demux);
err_dmx:
	dvb_unregister_adapter(&fc->dvb_adapter);
	return ret;
}