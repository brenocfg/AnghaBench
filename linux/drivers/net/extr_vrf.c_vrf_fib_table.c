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
typedef  int /*<<< orphan*/  u32 ;
struct net_vrf {int /*<<< orphan*/  tb_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_vrf* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static u32 vrf_fib_table(const struct net_device *dev)
{
	struct net_vrf *vrf = netdev_priv(dev);

	return vrf->tb_id;
}