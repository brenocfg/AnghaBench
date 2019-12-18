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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  fw_ver; } ;
struct qedr_dev {TYPE_1__ attr; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_FW_VERSION_NAME_MAX ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 

__attribute__((used)) static void qedr_get_dev_fw_str(struct ib_device *ibdev, char *str)
{
	struct qedr_dev *qedr = get_qedr_dev(ibdev);
	u32 fw_ver = (u32)qedr->attr.fw_ver;

	snprintf(str, IB_FW_VERSION_NAME_MAX, "%d.%d.%d.%d",
		 (fw_ver >> 24) & 0xFF, (fw_ver >> 16) & 0xFF,
		 (fw_ver >> 8) & 0xFF, fw_ver & 0xFF);
}