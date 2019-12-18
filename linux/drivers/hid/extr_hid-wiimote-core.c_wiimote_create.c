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
struct TYPE_4__ {int cmd_battery; int /*<<< orphan*/  drm; int /*<<< orphan*/  sync; int /*<<< orphan*/  ready; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  worker; int /*<<< orphan*/  lock; } ;
struct wiimote_data {int /*<<< orphan*/  timer; int /*<<< orphan*/  init_worker; TYPE_2__ state; TYPE_1__ queue; struct hid_device* hdev; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIPROTO_REQ_DRM_K ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct wiimote_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct wiimote_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiimote_init_timeout ; 
 int /*<<< orphan*/  wiimote_init_worker ; 
 int /*<<< orphan*/  wiimote_queue_worker ; 

__attribute__((used)) static struct wiimote_data *wiimote_create(struct hid_device *hdev)
{
	struct wiimote_data *wdata;

	wdata = kzalloc(sizeof(*wdata), GFP_KERNEL);
	if (!wdata)
		return NULL;

	wdata->hdev = hdev;
	hid_set_drvdata(hdev, wdata);

	spin_lock_init(&wdata->queue.lock);
	INIT_WORK(&wdata->queue.worker, wiimote_queue_worker);

	spin_lock_init(&wdata->state.lock);
	init_completion(&wdata->state.ready);
	mutex_init(&wdata->state.sync);
	wdata->state.drm = WIIPROTO_REQ_DRM_K;
	wdata->state.cmd_battery = 0xff;

	INIT_WORK(&wdata->init_worker, wiimote_init_worker);
	timer_setup(&wdata->timer, wiimote_init_timeout, 0);

	return wdata;
}