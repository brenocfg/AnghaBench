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
struct edac_device_prv_data {int /*<<< orphan*/  inject_fops; } ;
struct edac_device_ctl_info {struct altr_edac_device_dev* pvt_info; } ;
struct altr_edac_device_dev {int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  edac_dev_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EDAC_DEBUG ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_debugfs_create_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct edac_device_ctl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altr_create_edacdev_dbgfs(struct edac_device_ctl_info *edac_dci,
				      const struct edac_device_prv_data *priv)
{
	struct altr_edac_device_dev *drvdata = edac_dci->pvt_info;

	if (!IS_ENABLED(CONFIG_EDAC_DEBUG))
		return;

	drvdata->debugfs_dir = edac_debugfs_create_dir(drvdata->edac_dev_name);
	if (!drvdata->debugfs_dir)
		return;

	if (!edac_debugfs_create_file("altr_trigger", S_IWUSR,
				      drvdata->debugfs_dir, edac_dci,
				      priv->inject_fops))
		debugfs_remove_recursive(drvdata->debugfs_dir);
}