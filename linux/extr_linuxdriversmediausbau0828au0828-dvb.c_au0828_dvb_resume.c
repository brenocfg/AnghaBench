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
struct au0828_dvb {int /*<<< orphan*/  lock; scalar_t__ frontend; } ;
struct au0828_dev {scalar_t__ need_urb_start; struct au0828_dvb dvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  au0828_start_transport (struct au0828_dev*) ; 
 int dvb_frontend_resume (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  start_urb_transfer (struct au0828_dev*) ; 

void au0828_dvb_resume(struct au0828_dev *dev)
{
	struct au0828_dvb *dvb = &dev->dvb;
	int rc;

	if (dvb->frontend) {
		/* resume frontend - does fe and tuner init */
		rc = dvb_frontend_resume(dvb->frontend);
		pr_info("au0828_dvb_resume(): Resuming DVB fe %d\n", rc);
		if (dev->need_urb_start) {
			/* Start transport */
			mutex_lock(&dvb->lock);
			au0828_start_transport(dev);
			start_urb_transfer(dev);
			mutex_unlock(&dvb->lock);
		}
	}
}