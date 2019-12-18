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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_RX_DIST_CLS ; 
 int dpaa2_eth_set_dist_key (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dpaa2_eth_set_cls(struct net_device *net_dev, u64 flags)
{
	return dpaa2_eth_set_dist_key(net_dev, DPAA2_ETH_RX_DIST_CLS, flags);
}