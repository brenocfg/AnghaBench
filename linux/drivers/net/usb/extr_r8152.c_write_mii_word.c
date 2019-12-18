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
struct r8152 {int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int R8152_PHY_ID ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  r8152_mdio_write (struct r8152*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void write_mii_word(struct net_device *netdev, int phy_id, int reg, int val)
{
	struct r8152 *tp = netdev_priv(netdev);

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (phy_id != R8152_PHY_ID)
		return;

	r8152_mdio_write(tp, reg, val);
}