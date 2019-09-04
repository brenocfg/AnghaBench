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
struct xgbe_prv_data {TYPE_1__* netdev; } ;
struct TYPE_2__ {unsigned int mtu; } ;

/* Variables and functions */
 unsigned int ETH_FCS_LEN ; 
 unsigned int ETH_HLEN ; 
 unsigned int VLAN_HLEN ; 

__attribute__((used)) static inline unsigned int xgbe_get_max_frame(struct xgbe_prv_data *pdata)
{
	return pdata->netdev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
}