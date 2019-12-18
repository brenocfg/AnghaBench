#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned int devtype; int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_5__* input; TYPE_4__ state; TYPE_3__* hdev; } ;
struct wiimod_ops {int flags; int (* probe ) (struct wiimod_ops const*,struct wiimote_data*) ;int /*<<< orphan*/  (* remove ) (struct wiimod_ops const*,struct wiimote_data*) ;} ;
typedef  size_t __u8 ;
struct TYPE_10__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; TYPE_2__ id; TYPE_1__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int WIIMOD_FLAG_INPUT ; 
 size_t const WIIMOD_NULL ; 
 int /*<<< orphan*/  WIIMOTE_NAME ; 
 TYPE_5__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_5__*) ; 
 int input_register_device (TYPE_5__*) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_5__*,struct wiimote_data*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct wiimod_ops const*,struct wiimote_data*) ; 
 int /*<<< orphan*/  stub2 (struct wiimod_ops const*,struct wiimote_data*) ; 
 struct wiimod_ops** wiimod_table ; 
 size_t** wiimote_devtype_mods ; 

__attribute__((used)) static void wiimote_modules_load(struct wiimote_data *wdata,
				 unsigned int devtype)
{
	bool need_input = false;
	const __u8 *mods, *iter;
	const struct wiimod_ops *ops;
	int ret;

	mods = wiimote_devtype_mods[devtype];

	for (iter = mods; *iter != WIIMOD_NULL; ++iter) {
		if (wiimod_table[*iter]->flags & WIIMOD_FLAG_INPUT) {
			need_input = true;
			break;
		}
	}

	if (need_input) {
		wdata->input = input_allocate_device();
		if (!wdata->input)
			return;

		input_set_drvdata(wdata->input, wdata);
		wdata->input->dev.parent = &wdata->hdev->dev;
		wdata->input->id.bustype = wdata->hdev->bus;
		wdata->input->id.vendor = wdata->hdev->vendor;
		wdata->input->id.product = wdata->hdev->product;
		wdata->input->id.version = wdata->hdev->version;
		wdata->input->name = WIIMOTE_NAME;
	}

	for (iter = mods; *iter != WIIMOD_NULL; ++iter) {
		ops = wiimod_table[*iter];
		if (!ops->probe)
			continue;

		ret = ops->probe(ops, wdata);
		if (ret)
			goto error;
	}

	if (wdata->input) {
		ret = input_register_device(wdata->input);
		if (ret)
			goto error;
	}

	spin_lock_irq(&wdata->state.lock);
	wdata->state.devtype = devtype;
	spin_unlock_irq(&wdata->state.lock);
	return;

error:
	for ( ; iter-- != mods; ) {
		ops = wiimod_table[*iter];
		if (ops->remove)
			ops->remove(ops, wdata);
	}

	if (wdata->input) {
		input_free_device(wdata->input);
		wdata->input = NULL;
	}
}