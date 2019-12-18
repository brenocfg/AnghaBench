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
struct wl1271 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_bt_coex_state ; 
 int /*<<< orphan*/  dev_attr_hw_pg_ver ; 
 int device_create_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwlog_attr ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wlcore_sysfs_init(struct wl1271 *wl)
{
	int ret;

	/* Create sysfs file to control bt coex state */
	ret = device_create_file(wl->dev, &dev_attr_bt_coex_state);
	if (ret < 0) {
		wl1271_error("failed to create sysfs file bt_coex_state");
		goto out;
	}

	/* Create sysfs file to get HW PG version */
	ret = device_create_file(wl->dev, &dev_attr_hw_pg_ver);
	if (ret < 0) {
		wl1271_error("failed to create sysfs file hw_pg_ver");
		goto out_bt_coex_state;
	}

	/* Create sysfs file for the FW log */
	ret = device_create_bin_file(wl->dev, &fwlog_attr);
	if (ret < 0) {
		wl1271_error("failed to create sysfs file fwlog");
		goto out_hw_pg_ver;
	}

	goto out;

out_hw_pg_ver:
	device_remove_file(wl->dev, &dev_attr_hw_pg_ver);

out_bt_coex_state:
	device_remove_file(wl->dev, &dev_attr_bt_coex_state);

out:
	return ret;
}