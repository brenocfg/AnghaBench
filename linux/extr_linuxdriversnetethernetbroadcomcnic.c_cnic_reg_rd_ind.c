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
struct drv_ctl_io {int /*<<< orphan*/  data; int /*<<< orphan*/  offset; } ;
struct TYPE_2__ {struct drv_ctl_io io; } ;
struct drv_ctl_info {int /*<<< orphan*/  cmd; TYPE_1__ data; } ;
struct cnic_local {struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int /*<<< orphan*/  (* drv_ctl ) (int /*<<< orphan*/ ,struct drv_ctl_info*) ;} ;
struct cnic_dev {int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_CTL_IO_RD_CMD ; 
 int /*<<< orphan*/  memset (struct drv_ctl_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct drv_ctl_info*) ; 

__attribute__((used)) static u32 cnic_reg_rd_ind(struct cnic_dev *dev, u32 off)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	struct drv_ctl_info info;
	struct drv_ctl_io *io = &info.data.io;

	memset(&info, 0, sizeof(struct drv_ctl_info));
	info.cmd = DRV_CTL_IO_RD_CMD;
	io->offset = off;
	ethdev->drv_ctl(dev->netdev, &info);
	return io->data;
}