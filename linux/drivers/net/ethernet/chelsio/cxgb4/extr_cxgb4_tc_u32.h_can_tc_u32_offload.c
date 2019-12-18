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
struct net_device {int features; } ;
struct adapter {scalar_t__ tc_u32; } ;

/* Variables and functions */
 int NETIF_F_HW_TC ; 
 struct adapter* netdev2adap (struct net_device*) ; 

__attribute__((used)) static inline bool can_tc_u32_offload(struct net_device *dev)
{
	struct adapter *adap = netdev2adap(dev);

	return (dev->features & NETIF_F_HW_TC) && adap->tc_u32 ? true : false;
}