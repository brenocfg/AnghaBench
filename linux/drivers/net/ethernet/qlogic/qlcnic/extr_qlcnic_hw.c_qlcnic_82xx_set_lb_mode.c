#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VPORT_MISS_MODE_ACCEPT_ALL ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ qlcnic_nic_set_promisc (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_set_fw_loopback (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

int qlcnic_82xx_set_lb_mode(struct qlcnic_adapter *adapter, u8 mode)
{
	if (qlcnic_set_fw_loopback(adapter, mode))
		return -EIO;

	if (qlcnic_nic_set_promisc(adapter,
				   VPORT_MISS_MODE_ACCEPT_ALL)) {
		qlcnic_set_fw_loopback(adapter, 0);
		return -EIO;
	}

	msleep(1000);
	return 0;
}