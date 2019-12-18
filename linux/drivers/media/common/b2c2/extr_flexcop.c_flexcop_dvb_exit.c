#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close ) (TYPE_1__*) ;} ;
struct TYPE_6__ {TYPE_1__ dmx; } ;
struct flexcop_device {int init_state; int /*<<< orphan*/  dvb_adapter; TYPE_4__ demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  hw_frontend; int /*<<< orphan*/  mem_frontend; int /*<<< orphan*/  dvbnet; } ;

/* Variables and functions */
 int FC_STATE_DVB_INIT ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_4__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flexcop_dvb_exit(struct flexcop_device *fc)
{
	if (fc->init_state & FC_STATE_DVB_INIT) {
		dvb_net_release(&fc->dvbnet);

		fc->demux.dmx.close(&fc->demux.dmx);
		fc->demux.dmx.remove_frontend(&fc->demux.dmx,
			&fc->mem_frontend);
		fc->demux.dmx.remove_frontend(&fc->demux.dmx,
			&fc->hw_frontend);
		dvb_dmxdev_release(&fc->dmxdev);
		dvb_dmx_release(&fc->demux);
		dvb_unregister_adapter(&fc->dvb_adapter);
		deb_info("deinitialized dvb stuff\n");
	}
	fc->init_state &= ~FC_STATE_DVB_INIT;
}