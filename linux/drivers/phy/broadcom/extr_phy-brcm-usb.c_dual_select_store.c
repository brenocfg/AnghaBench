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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct brcm_usb_phy_data {int /*<<< orphan*/  ini; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * brcm_dual_mode_to_name ; 
 int /*<<< orphan*/  brcm_usb_init_set_dual_select (int /*<<< orphan*/ *,int) ; 
 struct brcm_usb_phy_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int name_to_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int*) ; 
 int /*<<< orphan*/  sysfs_lock ; 

__attribute__((used)) static ssize_t dual_select_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t len)
{
	struct brcm_usb_phy_data *priv = dev_get_drvdata(dev);
	int value;
	int res;

	mutex_lock(&sysfs_lock);
	res = name_to_value(&brcm_dual_mode_to_name[0],
			    ARRAY_SIZE(brcm_dual_mode_to_name), buf, &value);
	if (!res) {
		brcm_usb_init_set_dual_select(&priv->ini, value);
		res = len;
	}
	mutex_unlock(&sysfs_lock);
	return res;
}