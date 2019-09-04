#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bnxt_re_dev {TYPE_2__* en_dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_3__ ibdev ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct bnxt_re_dev* to_bnxt_re_dev (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_rev(struct device *device, struct device_attribute *attr,
			char *buf)
{
	struct bnxt_re_dev *rdev = to_bnxt_re_dev(device, ibdev.dev);

	return scnprintf(buf, PAGE_SIZE, "0x%x\n", rdev->en_dev->pdev->vendor);
}