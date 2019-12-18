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
struct port_info {int /*<<< orphan*/  eth_flags; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int /*<<< orphan*/  eth_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_FLAGS_ADAP ; 
 int /*<<< orphan*/  PRIV_FLAGS_PORT ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb4_set_priv_flags(struct net_device *netdev, u32 flags)
{
	struct port_info *pi = netdev_priv(netdev);
	struct adapter *adapter = pi->adapter;

	set_flags(&adapter->eth_flags, flags, PRIV_FLAGS_ADAP);
	set_flags(&pi->eth_flags, flags, PRIV_FLAGS_PORT);

	return 0;
}