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
struct ib_device {int dummy; } ;
struct TYPE_2__ {int* fw_ver; } ;
struct bnxt_re_dev {TYPE_1__ dev_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_FW_VERSION_NAME_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 struct bnxt_re_dev* to_bnxt_re_dev (struct ib_device*,struct ib_device*) ; 

void bnxt_re_query_fw_str(struct ib_device *ibdev, char *str)
{
	struct bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);

	snprintf(str, IB_FW_VERSION_NAME_MAX, "%d.%d.%d.%d",
		 rdev->dev_attr.fw_ver[0], rdev->dev_attr.fw_ver[1],
		 rdev->dev_attr.fw_ver[2], rdev->dev_attr.fw_ver[3]);
}