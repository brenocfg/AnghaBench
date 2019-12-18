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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  blackhole_netdev_ops ; 
 int /*<<< orphan*/  gen_lo_setup (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blackhole_netdev_setup(struct net_device *dev)
{
	gen_lo_setup(dev, ETH_MIN_MTU, NULL, NULL, &blackhole_netdev_ops, NULL);
}