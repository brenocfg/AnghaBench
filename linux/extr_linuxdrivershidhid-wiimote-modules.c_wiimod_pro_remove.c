#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/ * input; } ;
struct wiimote_data {TYPE_2__ state; TYPE_1__* hdev; int /*<<< orphan*/  rumble_worker; TYPE_3__ extension; } ;
struct wiimod_ops {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_pro_calib ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wiiproto_req_rumble (struct wiimote_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wiimod_pro_remove(const struct wiimod_ops *ops,
			      struct wiimote_data *wdata)
{
	unsigned long flags;

	if (!wdata->extension.input)
		return;

	input_unregister_device(wdata->extension.input);
	wdata->extension.input = NULL;
	cancel_work_sync(&wdata->rumble_worker);
	device_remove_file(&wdata->hdev->dev,
			   &dev_attr_pro_calib);

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiiproto_req_rumble(wdata, 0);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
}