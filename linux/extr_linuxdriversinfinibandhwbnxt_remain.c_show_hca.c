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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  node_desc; } ;
struct bnxt_re_dev {TYPE_1__ ibdev; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_2__ ibdev ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct bnxt_re_dev* to_bnxt_re_dev (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_hca(struct device *device, struct device_attribute *attr,
			char *buf)
{
	struct bnxt_re_dev *rdev = to_bnxt_re_dev(device, ibdev.dev);

	return scnprintf(buf, PAGE_SIZE, "%s\n", rdev->ibdev.node_desc);
}