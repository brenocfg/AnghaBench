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
struct TYPE_4__ {int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ dmx; } ;
struct mantis_pci {int /*<<< orphan*/  dvb_adapter; TYPE_3__ demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  fe_hw; int /*<<< orphan*/  fe_mem; int /*<<< orphan*/  dvbnet; int /*<<< orphan*/  tasklet; scalar_t__ fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_3__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (scalar_t__) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (scalar_t__) ; 
 int mantis_frontend_shutdown (struct mantis_pci*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

int mantis_dvb_exit(struct mantis_pci *mantis)
{
	int err;

	if (mantis->fe) {
		/* mantis_ca_exit(mantis); */
		err = mantis_frontend_shutdown(mantis);
		if (err != 0)
			dprintk(MANTIS_ERROR, 1, "Frontend exit while POWER ON! <%d>", err);
		dvb_unregister_frontend(mantis->fe);
		dvb_frontend_detach(mantis->fe);
	}

	tasklet_kill(&mantis->tasklet);
	dvb_net_release(&mantis->dvbnet);

	mantis->demux.dmx.remove_frontend(&mantis->demux.dmx, &mantis->fe_mem);
	mantis->demux.dmx.remove_frontend(&mantis->demux.dmx, &mantis->fe_hw);

	dvb_dmxdev_release(&mantis->dmxdev);
	dvb_dmx_release(&mantis->demux);

	dprintk(MANTIS_DEBUG, 1, "dvb_unregister_adapter");
	dvb_unregister_adapter(&mantis->dvb_adapter);

	return 0;
}