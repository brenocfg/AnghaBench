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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  credit_count; } ;
struct TYPE_4__ {TYPE_1__ credit; } ;
struct drv_ctl_info {int cmd; TYPE_2__ data; } ;
struct cnic_local {struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int /*<<< orphan*/  (* drv_ctl ) (int /*<<< orphan*/ ,struct drv_ctl_info*) ;} ;
struct cnic_dev {int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct drv_ctl_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct drv_ctl_info*) ; 

__attribute__((used)) static void cnic_spq_completion(struct cnic_dev *dev, int cmd, u32 count)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	struct drv_ctl_info info;

	memset(&info, 0, sizeof(struct drv_ctl_info));
	info.cmd = cmd;
	info.data.credit.credit_count = count;
	ethdev->drv_ctl(dev->netdev, &info);
}