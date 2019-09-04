#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (TYPE_1__*) ;} ;
struct TYPE_4__ {TYPE_1__ dmx; } ;
struct pvr2_dvb_adapter {int /*<<< orphan*/  dvb_adap; TYPE_2__ demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  dvb_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_INFO ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_2__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int pvr2_dvb_adapter_exit(struct pvr2_dvb_adapter *adap)
{
	pvr2_trace(PVR2_TRACE_INFO, "unregistering DVB devices");
	dvb_net_release(&adap->dvb_net);
	adap->demux.dmx.close(&adap->demux.dmx);
	dvb_dmxdev_release(&adap->dmxdev);
	dvb_dmx_release(&adap->demux);
	dvb_unregister_adapter(&adap->dvb_adap);
	return 0;
}