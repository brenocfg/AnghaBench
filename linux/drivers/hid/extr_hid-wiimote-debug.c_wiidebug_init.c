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
struct wiimote_debug {void* eeprom; void* drm; struct wiimote_data* wdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_2__ state; struct wiimote_debug* debug; TYPE_1__* hdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  debug_dir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_IRUSR ; 
 void* debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wiimote_debug*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (void*) ; 
 int /*<<< orphan*/  kfree (struct wiimote_debug*) ; 
 struct wiimote_debug* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wiidebug_drm_fops ; 
 int /*<<< orphan*/  wiidebug_eeprom_fops ; 

int wiidebug_init(struct wiimote_data *wdata)
{
	struct wiimote_debug *dbg;
	unsigned long flags;
	int ret = -ENOMEM;

	dbg = kzalloc(sizeof(*dbg), GFP_KERNEL);
	if (!dbg)
		return -ENOMEM;

	dbg->wdata = wdata;

	dbg->eeprom = debugfs_create_file("eeprom", S_IRUSR,
		dbg->wdata->hdev->debug_dir, dbg, &wiidebug_eeprom_fops);
	if (!dbg->eeprom)
		goto err;

	dbg->drm = debugfs_create_file("drm", S_IRUSR,
			dbg->wdata->hdev->debug_dir, dbg, &wiidebug_drm_fops);
	if (!dbg->drm)
		goto err_drm;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->debug = dbg;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	return 0;

err_drm:
	debugfs_remove(dbg->eeprom);
err:
	kfree(dbg);
	return ret;
}