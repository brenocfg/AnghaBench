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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vivid_dev {long cec_xfer_time_jiffies; void* cec_xfer_start_jiffies; int /*<<< orphan*/  cec_slock; int /*<<< orphan*/  cec_work_list; } ;
struct cec_msg {int len; } ;
struct vivid_cec_work {int /*<<< orphan*/  work; scalar_t__ usecs; int /*<<< orphan*/  list; struct cec_msg msg; struct cec_adapter* adap; struct vivid_dev* dev; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ CEC_FREE_TIME_TO_USEC (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int USECS_PER_BYTE ; 
 struct vivid_dev* cec_get_drvdata (struct cec_adapter*) ; 
 void* jiffies ; 
 struct vivid_cec_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 long usecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  vivid_cec_xfer_done_worker ; 
 int /*<<< orphan*/  vivid_cec_xfer_try_worker ; 

__attribute__((used)) static int vivid_cec_adap_transmit(struct cec_adapter *adap, u8 attempts,
				   u32 signal_free_time, struct cec_msg *msg)
{
	struct vivid_dev *dev = cec_get_drvdata(adap);
	struct vivid_cec_work *cw = kzalloc(sizeof(*cw), GFP_KERNEL);
	long delta_jiffies = 0;

	if (cw == NULL)
		return -ENOMEM;
	cw->dev = dev;
	cw->adap = adap;
	cw->usecs = CEC_FREE_TIME_TO_USEC(signal_free_time) +
		    msg->len * USECS_PER_BYTE;
	cw->msg = *msg;

	spin_lock(&dev->cec_slock);
	list_add(&cw->list, &dev->cec_work_list);
	if (dev->cec_xfer_time_jiffies == 0) {
		INIT_DELAYED_WORK(&cw->work, vivid_cec_xfer_done_worker);
		dev->cec_xfer_start_jiffies = jiffies;
		dev->cec_xfer_time_jiffies = usecs_to_jiffies(cw->usecs);
		delta_jiffies = dev->cec_xfer_time_jiffies;
	} else {
		INIT_DELAYED_WORK(&cw->work, vivid_cec_xfer_try_worker);
		delta_jiffies = dev->cec_xfer_start_jiffies +
			dev->cec_xfer_time_jiffies - jiffies;
	}
	spin_unlock(&dev->cec_slock);
	schedule_delayed_work(&cw->work, delta_jiffies < 0 ? 0 : delta_jiffies);
	return 0;
}