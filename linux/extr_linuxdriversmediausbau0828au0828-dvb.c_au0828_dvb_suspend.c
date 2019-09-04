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
struct au0828_dvb {scalar_t__ frontend; int /*<<< orphan*/  lock; } ;
struct au0828_dev {int need_urb_start; int /*<<< orphan*/  restart_streaming; scalar_t__ urb_streaming; struct au0828_dvb dvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  au0828_stop_transport (struct au0828_dev*,int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int dvb_frontend_suspend (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  stop_urb_transfer (struct au0828_dev*) ; 

void au0828_dvb_suspend(struct au0828_dev *dev)
{
	struct au0828_dvb *dvb = &dev->dvb;
	int rc;

	if (dvb->frontend) {
		if (dev->urb_streaming) {
			cancel_work_sync(&dev->restart_streaming);
			/* Stop transport */
			mutex_lock(&dvb->lock);
			stop_urb_transfer(dev);
			au0828_stop_transport(dev, 1);
			mutex_unlock(&dvb->lock);
			dev->need_urb_start = true;
		}
		/* suspend frontend - does tuner and fe to sleep */
		rc = dvb_frontend_suspend(dvb->frontend);
		pr_info("au0828_dvb_suspend(): Suspending DVB fe %d\n", rc);
	}
}