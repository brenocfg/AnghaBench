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
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  rev ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_CFG_ID ; 
 int fw_cfg_do_platform_probe (struct platform_device*) ; 
 int /*<<< orphan*/  fw_cfg_fname_kset ; 
 int /*<<< orphan*/  fw_cfg_io_cleanup () ; 
 int /*<<< orphan*/  fw_cfg_kobj_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  fw_cfg_kset_unregister_recursive (int /*<<< orphan*/ ) ; 
 int fw_cfg_read_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int fw_cfg_register_dir_entries () ; 
 int /*<<< orphan*/  fw_cfg_rev ; 
 TYPE_1__ fw_cfg_rev_attr ; 
 scalar_t__ fw_cfg_sel_ko ; 
 int /*<<< orphan*/  fw_cfg_sysfs_cache_cleanup () ; 
 int /*<<< orphan*/  fw_cfg_top_ko ; 
 scalar_t__ kobject_create_and_add (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int sysfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fw_cfg_sysfs_probe(struct platform_device *pdev)
{
	int err;
	__le32 rev;

	/* NOTE: If we supported multiple fw_cfg devices, we'd first create
	 * a subdirectory named after e.g. pdev->id, then hang per-device
	 * by_key (and by_name) subdirectories underneath it. However, only
	 * one fw_cfg device exist system-wide, so if one was already found
	 * earlier, we might as well stop here.
	 */
	if (fw_cfg_sel_ko)
		return -EBUSY;

	/* create by_key and by_name subdirs of /sys/firmware/qemu_fw_cfg/ */
	err = -ENOMEM;
	fw_cfg_sel_ko = kobject_create_and_add("by_key", fw_cfg_top_ko);
	if (!fw_cfg_sel_ko)
		goto err_sel;
	fw_cfg_fname_kset = kset_create_and_add("by_name", NULL, fw_cfg_top_ko);
	if (!fw_cfg_fname_kset)
		goto err_name;

	/* initialize fw_cfg device i/o from platform data */
	err = fw_cfg_do_platform_probe(pdev);
	if (err)
		goto err_probe;

	/* get revision number, add matching top-level attribute */
	err = fw_cfg_read_blob(FW_CFG_ID, &rev, 0, sizeof(rev));
	if (err < 0)
		goto err_probe;

	fw_cfg_rev = le32_to_cpu(rev);
	err = sysfs_create_file(fw_cfg_top_ko, &fw_cfg_rev_attr.attr);
	if (err)
		goto err_rev;

	/* process fw_cfg file directory entry, registering each file */
	err = fw_cfg_register_dir_entries();
	if (err)
		goto err_dir;

	/* success */
	pr_debug("fw_cfg: loaded.\n");
	return 0;

err_dir:
	fw_cfg_sysfs_cache_cleanup();
	sysfs_remove_file(fw_cfg_top_ko, &fw_cfg_rev_attr.attr);
err_rev:
	fw_cfg_io_cleanup();
err_probe:
	fw_cfg_kset_unregister_recursive(fw_cfg_fname_kset);
err_name:
	fw_cfg_kobj_cleanup(fw_cfg_sel_ko);
err_sel:
	return err;
}