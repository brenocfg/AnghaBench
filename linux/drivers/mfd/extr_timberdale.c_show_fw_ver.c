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
struct TYPE_2__ {int major; int minor; int config; } ;
struct timberdale_device {TYPE_1__ fw; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct timberdale_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static ssize_t show_fw_ver(struct device *dev, struct device_attribute *attr,
	char *buf)
{
	struct timberdale_device *priv = dev_get_drvdata(dev);

	return sprintf(buf, "%d.%d.%d\n", priv->fw.major, priv->fw.minor,
		priv->fw.config);
}