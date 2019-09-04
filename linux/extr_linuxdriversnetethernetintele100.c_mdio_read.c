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
struct nic {int (* mdio_ctrl ) (struct nic*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdi_read ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct nic*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdio_read(struct net_device *netdev, int addr, int reg)
{
	struct nic *nic = netdev_priv(netdev);
	return nic->mdio_ctrl(nic, addr, mdi_read, reg, 0);
}