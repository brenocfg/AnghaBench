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
struct TYPE_2__ {int* mac_addr; } ;
struct port_info {TYPE_1__ iscsic; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cxgb3_init_iscsi_mac(struct net_device *dev)
{
	struct port_info *pi = netdev_priv(dev);

	memcpy(pi->iscsic.mac_addr, dev->dev_addr, ETH_ALEN);
	pi->iscsic.mac_addr[3] |= 0x80;
}