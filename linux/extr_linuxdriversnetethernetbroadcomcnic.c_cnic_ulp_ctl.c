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
struct fcoe_capabilities {int dummy; } ;
struct TYPE_3__ {struct fcoe_capabilities fcoe_features; } ;
struct TYPE_4__ {int ulp_type; TYPE_1__ register_data; } ;
struct drv_ctl_info {int drv_state; TYPE_2__ data; int /*<<< orphan*/  cmd; } ;
struct cnic_local {struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int /*<<< orphan*/  (* drv_ctl ) (int /*<<< orphan*/ ,struct drv_ctl_info*) ;} ;
struct cnic_dev {int /*<<< orphan*/  netdev; int /*<<< orphan*/  fcoe_cap; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int CNIC_ULP_FCOE ; 
 int /*<<< orphan*/  DRV_CTL_ULP_REGISTER_CMD ; 
 int /*<<< orphan*/  DRV_CTL_ULP_UNREGISTER_CMD ; 
 int /*<<< orphan*/  memcpy (struct fcoe_capabilities*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct drv_ctl_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct drv_ctl_info*) ; 

__attribute__((used)) static void cnic_ulp_ctl(struct cnic_dev *dev, int ulp_type, bool reg, int state)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	struct drv_ctl_info info;
	struct fcoe_capabilities *fcoe_cap =
		&info.data.register_data.fcoe_features;

	memset(&info, 0, sizeof(struct drv_ctl_info));
	if (reg) {
		info.cmd = DRV_CTL_ULP_REGISTER_CMD;
		if (ulp_type == CNIC_ULP_FCOE && dev->fcoe_cap)
			memcpy(fcoe_cap, dev->fcoe_cap, sizeof(*fcoe_cap));
	} else {
		info.cmd = DRV_CTL_ULP_UNREGISTER_CMD;
	}

	info.data.ulp_type = ulp_type;
	info.drv_state = state;
	ethdev->drv_ctl(dev->netdev, &info);
}