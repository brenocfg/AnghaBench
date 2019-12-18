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
typedef  int u32 ;
struct amd_mp2_dev {int dummy; } ;
struct TYPE_4__ {int length; int slave_addr; } ;
struct TYPE_5__ {TYPE_1__ r; } ;
struct amd_i2c_common {int cmd_success; TYPE_3__* msg; TYPE_2__ eventval; struct amd_mp2_dev* mp2_dev; } ;
struct TYPE_6__ {int len; int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ndev_dev (struct amd_mp2_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void amd_mp2_pci_check_rw_event(struct amd_i2c_common *i2c_common)
{
	struct amd_mp2_dev *privdata = i2c_common->mp2_dev;
	int len = i2c_common->eventval.r.length;
	u32 slave_addr = i2c_common->eventval.r.slave_addr;
	bool err = false;

	if (unlikely(len != i2c_common->msg->len)) {
		dev_err(ndev_dev(privdata),
			"length %d in event doesn't match buffer length %d!\n",
			len, i2c_common->msg->len);
		err = true;
	}

	if (unlikely(slave_addr != i2c_common->msg->addr)) {
		dev_err(ndev_dev(privdata),
			"unexpected slave address %x (expected: %x)!\n",
			slave_addr, i2c_common->msg->addr);
		err = true;
	}

	if (!err)
		i2c_common->cmd_success = true;
}