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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int EADDRNOTAVAIL ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_sample_bulletin (struct bnx2x*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_validate_addr(struct net_device *dev)
{
	struct bnx2x *bp = netdev_priv(dev);

	/* query the bulletin board for mac address configured by the PF */
	if (IS_VF(bp))
		bnx2x_sample_bulletin(bp);

	if (!is_valid_ether_addr(dev->dev_addr)) {
		BNX2X_ERR("Non-valid Ethernet address\n");
		return -EADDRNOTAVAIL;
	}
	return 0;
}