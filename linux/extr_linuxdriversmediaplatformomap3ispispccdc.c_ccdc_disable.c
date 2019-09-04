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
struct TYPE_2__ {int /*<<< orphan*/  free_queue; int /*<<< orphan*/  table_work; int /*<<< orphan*/ * active; int /*<<< orphan*/ * request; } ;
struct isp_ccdc_device {scalar_t__ state; scalar_t__ stopping; int /*<<< orphan*/  ioctl_lock; TYPE_1__ lsc; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 scalar_t__ CCDC_STOP_FINISHED ; 
 scalar_t__ CCDC_STOP_NOT_REQUESTED ; 
 scalar_t__ CCDC_STOP_REQUEST ; 
 int ETIMEDOUT ; 
 scalar_t__ ISP_PIPELINE_STREAM_CONTINUOUS ; 
 int /*<<< orphan*/  OMAP3_ISP_SBL_CCDC_LSC_READ ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_lsc_free_queue (struct isp_ccdc_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_lsc_free_request (struct isp_ccdc_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_sbl_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_device (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  to_isp_device (struct isp_ccdc_device*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccdc_disable(struct isp_ccdc_device *ccdc)
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&ccdc->lock, flags);
	if (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS)
		ccdc->stopping = CCDC_STOP_REQUEST;
	if (!ccdc->running)
		ccdc->stopping = CCDC_STOP_FINISHED;
	spin_unlock_irqrestore(&ccdc->lock, flags);

	ret = wait_event_timeout(ccdc->wait,
				 ccdc->stopping == CCDC_STOP_FINISHED,
				 msecs_to_jiffies(2000));
	if (ret == 0) {
		ret = -ETIMEDOUT;
		dev_warn(to_device(ccdc), "CCDC stop timeout!\n");
	}

	omap3isp_sbl_disable(to_isp_device(ccdc), OMAP3_ISP_SBL_CCDC_LSC_READ);

	mutex_lock(&ccdc->ioctl_lock);
	ccdc_lsc_free_request(ccdc, ccdc->lsc.request);
	ccdc->lsc.request = ccdc->lsc.active;
	ccdc->lsc.active = NULL;
	cancel_work_sync(&ccdc->lsc.table_work);
	ccdc_lsc_free_queue(ccdc, &ccdc->lsc.free_queue);
	mutex_unlock(&ccdc->ioctl_lock);

	ccdc->stopping = CCDC_STOP_NOT_REQUESTED;

	return ret > 0 ? 0 : ret;
}