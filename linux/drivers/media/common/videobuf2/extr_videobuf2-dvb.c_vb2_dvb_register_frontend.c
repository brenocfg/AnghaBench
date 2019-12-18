#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {int capabilities; int (* add_frontend ) (TYPE_1__*,TYPE_2__*) ;int (* connect_frontend ) (TYPE_1__*,TYPE_2__*) ;int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,TYPE_2__*) ;} ;
struct TYPE_17__ {int filternum; int feednum; TYPE_1__ dmx; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; struct vb2_dvb* priv; } ;
struct TYPE_16__ {int filternum; scalar_t__ capabilities; TYPE_1__* demux; } ;
struct TYPE_19__ {int /*<<< orphan*/  source; } ;
struct vb2_dvb {int /*<<< orphan*/ * frontend; TYPE_14__ demux; TYPE_12__ dmxdev; TYPE_2__ fe_hw; TYPE_2__ fe_mem; int /*<<< orphan*/  name; int /*<<< orphan*/  net; } ;
struct dvb_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_FRONTEND_0 ; 
 int DMX_MEMORY_BASED_FILTERING ; 
 int /*<<< orphan*/  DMX_MEMORY_FE ; 
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 int dvb_dmx_init (TYPE_14__*) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_14__*) ; 
 int dvb_dmxdev_init (TYPE_12__*,struct dvb_adapter*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (TYPE_12__*) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int dvb_net_init (struct dvb_adapter*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dvb_register_frontend (struct dvb_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_1__*,TYPE_2__*) ; 
 int stub2 (TYPE_1__*,TYPE_2__*) ; 
 int stub3 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vb2_dvb_start_feed ; 
 int /*<<< orphan*/  vb2_dvb_stop_feed ; 

__attribute__((used)) static int vb2_dvb_register_frontend(struct dvb_adapter *adapter,
	struct vb2_dvb *dvb)
{
	int result;

	/* register frontend */
	result = dvb_register_frontend(adapter, dvb->frontend);
	if (result < 0) {
		pr_warn("%s: dvb_register_frontend failed (errno = %d)\n",
		       dvb->name, result);
		goto fail_frontend;
	}

	/* register demux stuff */
	dvb->demux.dmx.capabilities =
		DMX_TS_FILTERING | DMX_SECTION_FILTERING |
		DMX_MEMORY_BASED_FILTERING;
	dvb->demux.priv       = dvb;
	dvb->demux.filternum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.start_feed = vb2_dvb_start_feed;
	dvb->demux.stop_feed  = vb2_dvb_stop_feed;
	result = dvb_dmx_init(&dvb->demux);
	if (result < 0) {
		pr_warn("%s: dvb_dmx_init failed (errno = %d)\n",
		       dvb->name, result);
		goto fail_dmx;
	}

	dvb->dmxdev.filternum    = 256;
	dvb->dmxdev.demux        = &dvb->demux.dmx;
	dvb->dmxdev.capabilities = 0;
	result = dvb_dmxdev_init(&dvb->dmxdev, adapter);

	if (result < 0) {
		pr_warn("%s: dvb_dmxdev_init failed (errno = %d)\n",
		       dvb->name, result);
		goto fail_dmxdev;
	}

	dvb->fe_hw.source = DMX_FRONTEND_0;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (result < 0) {
		pr_warn("%s: add_frontend failed (DMX_FRONTEND_0, errno = %d)\n",
		       dvb->name, result);
		goto fail_fe_hw;
	}

	dvb->fe_mem.source = DMX_MEMORY_FE;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	if (result < 0) {
		pr_warn("%s: add_frontend failed (DMX_MEMORY_FE, errno = %d)\n",
		       dvb->name, result);
		goto fail_fe_mem;
	}

	result = dvb->demux.dmx.connect_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (result < 0) {
		pr_warn("%s: connect_frontend failed (errno = %d)\n",
		       dvb->name, result);
		goto fail_fe_conn;
	}

	/* register network adapter */
	result = dvb_net_init(adapter, &dvb->net, &dvb->demux.dmx);
	if (result < 0) {
		pr_warn("%s: dvb_net_init failed (errno = %d)\n",
		       dvb->name, result);
		goto fail_fe_conn;
	}
	return 0;

fail_fe_conn:
	dvb->demux.dmx.remove_frontend(&dvb->demux.dmx, &dvb->fe_mem);
fail_fe_mem:
	dvb->demux.dmx.remove_frontend(&dvb->demux.dmx, &dvb->fe_hw);
fail_fe_hw:
	dvb_dmxdev_release(&dvb->dmxdev);
fail_dmxdev:
	dvb_dmx_release(&dvb->demux);
fail_dmx:
	dvb_unregister_frontend(dvb->frontend);
fail_frontend:
	dvb_frontend_detach(dvb->frontend);
	dvb->frontend = NULL;

	return result;
}