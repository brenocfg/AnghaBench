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
struct hl_device {int asic_type; int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  ASIC_GOYA 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct hl_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t device_type_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct hl_device *hdev = dev_get_drvdata(dev);
	char *str;

	switch (hdev->asic_type) {
	case ASIC_GOYA:
		str = "GOYA";
		break;
	default:
		dev_err(hdev->dev, "Unrecognized ASIC type %d\n",
				hdev->asic_type);
		return -EINVAL;
	}

	return sprintf(buf, "%s\n", str);
}