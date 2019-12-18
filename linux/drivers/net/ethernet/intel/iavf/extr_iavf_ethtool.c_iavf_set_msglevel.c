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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int debug_mask; } ;
struct iavf_adapter {int msg_enable; TYPE_1__ hw; } ;

/* Variables and functions */
 int IAVF_DEBUG_USER ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void iavf_set_msglevel(struct net_device *netdev, u32 data)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);

	if (IAVF_DEBUG_USER & data)
		adapter->hw.debug_mask = data;
	adapter->msg_enable = data;
}