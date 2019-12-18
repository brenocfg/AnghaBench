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
typedef  scalar_t__ u8 ;
struct cosm_device {scalar_t__ state; scalar_t__ prev_state; int heartbeat_watchdog_enable; int /*<<< orphan*/  scif_work; int /*<<< orphan*/  cosm_mutex; TYPE_1__* hw_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* post_reset ) (struct cosm_device*,scalar_t__) ;int /*<<< orphan*/  (* stop ) (struct cosm_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_NOP ; 
 scalar_t__ MIC_READY ; 
 scalar_t__ MIC_RESETTING ; 
 scalar_t__ MIC_RESET_FAILED ; 
 int /*<<< orphan*/  cosm_hw_reset (struct cosm_device*,int) ; 
 int /*<<< orphan*/  cosm_set_shutdown_status (struct cosm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosm_set_state (struct cosm_device*,scalar_t__) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cosm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct cosm_device*,scalar_t__) ; 

void cosm_stop(struct cosm_device *cdev, bool force)
{
	mutex_lock(&cdev->cosm_mutex);
	if (cdev->state != MIC_READY || force) {
		/*
		 * Don't call hw_ops if they have been called previously.
		 * stop(..) calls device_unregister and will crash the system if
		 * called multiple times.
		 */
		u8 state = cdev->state == MIC_RESETTING ?
					cdev->prev_state : cdev->state;
		bool call_hw_ops = state != MIC_RESET_FAILED &&
					state != MIC_READY;

		if (cdev->state != MIC_RESETTING)
			cosm_set_state(cdev, MIC_RESETTING);
		cdev->heartbeat_watchdog_enable = false;
		if (call_hw_ops)
			cdev->hw_ops->stop(cdev, force);
		cosm_hw_reset(cdev, force);
		cosm_set_shutdown_status(cdev, MIC_NOP);
		if (call_hw_ops && cdev->hw_ops->post_reset)
			cdev->hw_ops->post_reset(cdev, cdev->state);
	}
	mutex_unlock(&cdev->cosm_mutex);
	flush_work(&cdev->scif_work);
}