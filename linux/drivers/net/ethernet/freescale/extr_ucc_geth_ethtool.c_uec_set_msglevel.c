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
typedef  int /*<<< orphan*/  uint32_t ;
struct ucc_geth_private {int /*<<< orphan*/  msg_enable; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct ucc_geth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
uec_set_msglevel(struct net_device *netdev, uint32_t data)
{
	struct ucc_geth_private *ugeth = netdev_priv(netdev);
	ugeth->msg_enable = data;
}