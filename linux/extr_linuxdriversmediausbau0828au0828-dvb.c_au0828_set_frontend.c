#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {TYPE_1__* dvb; } ;
struct au0828_dvb {int (* set_frontend ) (struct dvb_frontend*) ;int /*<<< orphan*/  lock; } ;
struct au0828_dev {int urb_streaming; int /*<<< orphan*/  restart_streaming; struct au0828_dvb dvb; } ;
struct TYPE_2__ {struct au0828_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  au0828_start_transport (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_stop_transport (struct au0828_dev*,int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_urb_transfer (struct au0828_dev*) ; 
 int /*<<< orphan*/  stop_urb_transfer (struct au0828_dev*) ; 
 int stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int au0828_set_frontend(struct dvb_frontend *fe)
{
	struct au0828_dev *dev = fe->dvb->priv;
	struct au0828_dvb *dvb = &dev->dvb;
	int ret, was_streaming;

	mutex_lock(&dvb->lock);
	was_streaming = dev->urb_streaming;
	if (was_streaming) {
		au0828_stop_transport(dev, 1);

		/*
		 * We can't hold a mutex here, as the restart_streaming
		 * kthread may also hold it.
		 */
		mutex_unlock(&dvb->lock);
		cancel_work_sync(&dev->restart_streaming);
		mutex_lock(&dvb->lock);

		stop_urb_transfer(dev);
	}
	mutex_unlock(&dvb->lock);

	ret = dvb->set_frontend(fe);

	if (was_streaming) {
		mutex_lock(&dvb->lock);
		au0828_start_transport(dev);
		start_urb_transfer(dev);
		mutex_unlock(&dvb->lock);
	}

	return ret;
}