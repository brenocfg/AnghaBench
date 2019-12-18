#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_6__ {TYPE_1__** netdevs; int /*<<< orphan*/ * phy_port; } ;
struct TYPE_7__ {size_t num_ports; int /*<<< orphan*/  max_mtu; } ;
struct hns_roce_dev {TYPE_2__ iboe; TYPE_3__ caps; TYPE_4__* hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_mtu ) (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int hns_roce_set_mac (struct hns_roce_dev*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_setup_mtu_mac(struct hns_roce_dev *hr_dev)
{
	int ret;
	u8 i;

	for (i = 0; i < hr_dev->caps.num_ports; i++) {
		if (hr_dev->hw->set_mtu)
			hr_dev->hw->set_mtu(hr_dev, hr_dev->iboe.phy_port[i],
					    hr_dev->caps.max_mtu);
		ret = hns_roce_set_mac(hr_dev, i,
				       hr_dev->iboe.netdevs[i]->dev_addr);
		if (ret)
			return ret;
	}

	return 0;
}