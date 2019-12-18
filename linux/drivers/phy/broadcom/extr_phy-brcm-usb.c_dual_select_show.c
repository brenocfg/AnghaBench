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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * brcm_dual_mode_to_name ; 
 int brcm_usb_init_get_dual_select (int /*<<< orphan*/ *) ; 
 struct brcm_usb_phy_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  sysfs_lock ; 
 char* value_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t dual_select_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct brcm_usb_phy_data *priv = dev_get_drvdata(dev);
	int value;

	mutex_lock(&sysfs_lock);
	value = brcm_usb_init_get_dual_select(&priv->ini);
	mutex_unlock(&sysfs_lock);
	return sprintf(buf, "%s\n",
		value_to_name(&brcm_dual_mode_to_name[0],
			      ARRAY_SIZE(brcm_dual_mode_to_name),
			      value));
}