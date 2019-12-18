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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct TYPE_3__ {size_t* phy_port; } ;
struct hns_roce_dev {size_t** dev_addr; TYPE_2__* hw; TYPE_1__ iboe; } ;
struct TYPE_4__ {int (* set_mac ) (struct hns_roce_dev*,size_t,size_t*) ;} ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  memcmp (size_t*,size_t*,size_t) ; 
 int stub1 (struct hns_roce_dev*,size_t,size_t*) ; 

__attribute__((used)) static int hns_roce_set_mac(struct hns_roce_dev *hr_dev, u8 port, u8 *addr)
{
	u8 phy_port;
	u32 i = 0;

	if (!memcmp(hr_dev->dev_addr[port], addr, ETH_ALEN))
		return 0;

	for (i = 0; i < ETH_ALEN; i++)
		hr_dev->dev_addr[port][i] = addr[i];

	phy_port = hr_dev->iboe.phy_port[port];
	return hr_dev->hw->set_mac(hr_dev, phy_port, addr);
}