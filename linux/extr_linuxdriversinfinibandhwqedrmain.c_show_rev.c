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
struct qedr_dev {TYPE_1__* pdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct qedr_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_rev(struct device *device, struct device_attribute *attr,
			char *buf)
{
	struct qedr_dev *dev = dev_get_drvdata(device);

	return scnprintf(buf, PAGE_SIZE, "0x%x\n", dev->pdev->vendor);
}