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
struct TYPE_2__ {int flags; int /*<<< orphan*/  mac_addr; } ;
struct port_info {unsigned int iscsi_ipv4addr; TYPE_1__ iscsic; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void cxgb3i_set_private_ipv4addr(struct net_device *ndev,
						unsigned int addr)
{
	struct port_info *pi =  (struct port_info *)netdev_priv(ndev);

	pi->iscsic.flags = addr ? 1 : 0;
	pi->iscsi_ipv4addr = addr;
	if (addr)
		memcpy(pi->iscsic.mac_addr, ndev->dev_addr, ETH_ALEN);
}