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
typedef  int /*<<< orphan*/  u32 ;
struct rvt_dev_info {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_ibdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dc8051_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_FW_VERSION_NAME_MAX ; 
 int dc8051_ver_maj (int /*<<< orphan*/ ) ; 
 int dc8051_ver_min (int /*<<< orphan*/ ) ; 
 int dc8051_ver_patch (int /*<<< orphan*/ ) ; 
 TYPE_1__* dd_from_dev (struct hfi1_ibdev*) ; 
 struct hfi1_ibdev* dev_from_rdi (struct rvt_dev_info*) ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static void hfi1_get_dev_fw_str(struct ib_device *ibdev, char *str)
{
	struct rvt_dev_info *rdi = ib_to_rvt(ibdev);
	struct hfi1_ibdev *dev = dev_from_rdi(rdi);
	u32 ver = dd_from_dev(dev)->dc8051_ver;

	snprintf(str, IB_FW_VERSION_NAME_MAX, "%u.%u.%u", dc8051_ver_maj(ver),
		 dc8051_ver_min(ver), dc8051_ver_patch(ver));
}