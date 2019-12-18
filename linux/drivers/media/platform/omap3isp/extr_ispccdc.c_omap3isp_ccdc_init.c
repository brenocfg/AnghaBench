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
struct TYPE_4__ {scalar_t__ dcsubval; scalar_t__ oblen; } ;
struct TYPE_3__ {int /*<<< orphan*/  req_lock; int /*<<< orphan*/  free_queue; int /*<<< orphan*/  state; int /*<<< orphan*/  table_work; } ;
struct isp_ccdc_device {int /*<<< orphan*/  ioctl_lock; int /*<<< orphan*/  update; TYPE_2__ clamp; TYPE_1__ lsc; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;
struct isp_device {struct isp_ccdc_device isp_ccdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_STOP_NOT_REQUESTED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSC_STATE_STOPPED ; 
 int /*<<< orphan*/  OMAP3ISP_CCDC_BLCLAMP ; 
 int /*<<< orphan*/  ccdc_apply_controls (struct isp_ccdc_device*) ; 
 int ccdc_init_entities (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_lsc_free_table_work ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int omap3isp_ccdc_init(struct isp_device *isp)
{
	struct isp_ccdc_device *ccdc = &isp->isp_ccdc;
	int ret;

	spin_lock_init(&ccdc->lock);
	init_waitqueue_head(&ccdc->wait);
	mutex_init(&ccdc->ioctl_lock);

	ccdc->stopping = CCDC_STOP_NOT_REQUESTED;

	INIT_WORK(&ccdc->lsc.table_work, ccdc_lsc_free_table_work);
	ccdc->lsc.state = LSC_STATE_STOPPED;
	INIT_LIST_HEAD(&ccdc->lsc.free_queue);
	spin_lock_init(&ccdc->lsc.req_lock);

	ccdc->clamp.oblen = 0;
	ccdc->clamp.dcsubval = 0;

	ccdc->update = OMAP3ISP_CCDC_BLCLAMP;
	ccdc_apply_controls(ccdc);

	ret = ccdc_init_entities(ccdc);
	if (ret < 0) {
		mutex_destroy(&ccdc->ioctl_lock);
		return ret;
	}

	return 0;
}