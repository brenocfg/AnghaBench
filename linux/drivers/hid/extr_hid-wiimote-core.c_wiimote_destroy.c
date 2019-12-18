#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  worker; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct wiimote_data {TYPE_3__* hdev; TYPE_2__ queue; int /*<<< orphan*/  timer; int /*<<< orphan*/  init_worker; TYPE_1__ state; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIPROTO_FLAG_EXITING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_devtype ; 
 int /*<<< orphan*/  dev_attr_extension ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_hw_close (TYPE_3__*) ; 
 int /*<<< orphan*/  hid_hw_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct wiimote_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wiidebug_deinit (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_ext_unload (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_modules_unload (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_mp_unload (struct wiimote_data*) ; 

__attribute__((used)) static void wiimote_destroy(struct wiimote_data *wdata)
{
	unsigned long flags;

	wiidebug_deinit(wdata);

	/* prevent init_worker from being scheduled again */
	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_EXITING;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	cancel_work_sync(&wdata->init_worker);
	del_timer_sync(&wdata->timer);

	device_remove_file(&wdata->hdev->dev, &dev_attr_devtype);
	device_remove_file(&wdata->hdev->dev, &dev_attr_extension);

	wiimote_mp_unload(wdata);
	wiimote_ext_unload(wdata);
	wiimote_modules_unload(wdata);
	cancel_work_sync(&wdata->queue.worker);
	hid_hw_close(wdata->hdev);
	hid_hw_stop(wdata->hdev);

	kfree(wdata);
}