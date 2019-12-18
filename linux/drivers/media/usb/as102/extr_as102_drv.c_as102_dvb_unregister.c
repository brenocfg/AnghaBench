#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct as102_dev_t {int /*<<< orphan*/  name; int /*<<< orphan*/  dvb_adap; int /*<<< orphan*/  dvb_dmx; int /*<<< orphan*/  dvb_dmxdev; int /*<<< orphan*/  dvb_fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

void as102_dvb_unregister(struct as102_dev_t *as102_dev)
{
	/* unregister as102 frontend */
	dvb_unregister_frontend(as102_dev->dvb_fe);

	/* detach frontend */
	dvb_frontend_detach(as102_dev->dvb_fe);

	/* unregister demux device */
	dvb_dmxdev_release(&as102_dev->dvb_dmxdev);
	dvb_dmx_release(&as102_dev->dvb_dmx);

	/* unregister dvb adapter */
	dvb_unregister_adapter(&as102_dev->dvb_adap);

	pr_info("Unregistered device %s", as102_dev->name);
}