#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close ) (TYPE_1__*) ;} ;
struct TYPE_5__ {TYPE_1__ dmx; } ;
struct firedtv {int /*<<< orphan*/  adapter; TYPE_3__ demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  frontend; int /*<<< orphan*/  dvbnet; int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (TYPE_3__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdtv_ca_release (struct firedtv*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

void fdtv_dvb_unregister(struct firedtv *fdtv)
{
	fdtv_ca_release(fdtv);
	dvb_unregister_frontend(&fdtv->fe);
	dvb_net_release(&fdtv->dvbnet);
	fdtv->demux.dmx.close(&fdtv->demux.dmx);
	fdtv->demux.dmx.remove_frontend(&fdtv->demux.dmx, &fdtv->frontend);
	dvb_dmxdev_release(&fdtv->dmxdev);
	dvb_dmx_release(&fdtv->demux);
	dvb_unregister_adapter(&fdtv->adapter);
}