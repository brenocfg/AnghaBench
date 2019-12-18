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
struct TYPE_6__ {scalar_t__ hotkey_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int TPACPI_DBG_EXIT ; 
 int TPACPI_DBG_HKEY ; 
 int /*<<< orphan*/  dbg_printk (int,char*) ; 
 int /*<<< orphan*/  delete_attr_set (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ hotkey_dev_attributes ; 
 scalar_t__ hotkey_mask_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotkey_mutex ; 
 int /*<<< orphan*/  hotkey_orig_mask ; 
 int /*<<< orphan*/  hotkey_poll_stop_sync () ; 
 int hotkey_status_set (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_3__ tp_features ; 
 TYPE_2__* tpacpi_pdev ; 

__attribute__((used)) static void hotkey_exit(void)
{
#ifdef CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	mutex_lock(&hotkey_mutex);
	hotkey_poll_stop_sync();
	mutex_unlock(&hotkey_mutex);
#endif

	if (hotkey_dev_attributes)
		delete_attr_set(hotkey_dev_attributes, &tpacpi_pdev->dev.kobj);

	dbg_printk(TPACPI_DBG_EXIT | TPACPI_DBG_HKEY,
		   "restoring original HKEY status and mask\n");
	/* yes, there is a bitwise or below, we want the
	 * functions to be called even if one of them fail */
	if (((tp_features.hotkey_mask &&
	      hotkey_mask_set(hotkey_orig_mask)) |
	     hotkey_status_set(false)) != 0)
		pr_err("failed to restore hot key mask to BIOS defaults\n");
}