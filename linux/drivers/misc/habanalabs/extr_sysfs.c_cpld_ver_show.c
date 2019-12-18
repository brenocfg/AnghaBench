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
struct TYPE_3__ {int cpld_version; } ;
struct TYPE_4__ {TYPE_1__ armcp_info; } ;
struct hl_device {TYPE_2__ asic_prop; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct hl_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t cpld_ver_show(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct hl_device *hdev = dev_get_drvdata(dev);

	return sprintf(buf, "0x%08x\n",
			hdev->asic_prop.armcp_info.cpld_version);
}