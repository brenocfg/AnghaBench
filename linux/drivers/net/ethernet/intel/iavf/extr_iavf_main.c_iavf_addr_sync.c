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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct iavf_adapter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ iavf_add_filter (struct iavf_adapter*,int /*<<< orphan*/  const*) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int iavf_addr_sync(struct net_device *netdev, const u8 *addr)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);

	if (iavf_add_filter(adapter, addr))
		return 0;
	else
		return -ENOMEM;
}