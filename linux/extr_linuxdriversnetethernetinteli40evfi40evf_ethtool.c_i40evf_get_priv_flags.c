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
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct i40evf_priv_flags {int flag; } ;
struct i40evf_adapter {int flags; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 size_t I40EVF_PRIV_FLAGS_STR_LEN ; 
 struct i40evf_priv_flags* i40evf_gstrings_priv_flags ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 i40evf_get_priv_flags(struct net_device *netdev)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	u32 i, ret_flags = 0;

	for (i = 0; i < I40EVF_PRIV_FLAGS_STR_LEN; i++) {
		const struct i40evf_priv_flags *priv_flags;

		priv_flags = &i40evf_gstrings_priv_flags[i];

		if (priv_flags->flag & adapter->flags)
			ret_flags |= BIT(i);
	}

	return ret_flags;
}