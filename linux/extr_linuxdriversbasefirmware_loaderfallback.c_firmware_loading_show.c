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
struct fw_sysfs {scalar_t__ fw_priv; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  fw_lock ; 
 int fw_sysfs_loading (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct fw_sysfs* to_fw_sysfs (struct device*) ; 

__attribute__((used)) static ssize_t firmware_loading_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	int loading = 0;

	mutex_lock(&fw_lock);
	if (fw_sysfs->fw_priv)
		loading = fw_sysfs_loading(fw_sysfs->fw_priv);
	mutex_unlock(&fw_lock);

	return sprintf(buf, "%d\n", loading);
}