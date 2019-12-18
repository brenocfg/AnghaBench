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
struct ixgbe_adapter {TYPE_1__* vfinfo; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  vf_mac_addresses; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ ixgbe_add_mac_filter (struct ixgbe_adapter*,unsigned char*,int) ; 
 int /*<<< orphan*/  ixgbe_del_mac_filter (struct ixgbe_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_set_vf_mac(struct ixgbe_adapter *adapter,
			    int vf, unsigned char *mac_addr)
{
	s32 retval;

	ixgbe_del_mac_filter(adapter, adapter->vfinfo[vf].vf_mac_addresses, vf);
	retval = ixgbe_add_mac_filter(adapter, mac_addr, vf);
	if (retval >= 0)
		memcpy(adapter->vfinfo[vf].vf_mac_addresses, mac_addr,
		       ETH_ALEN);
	else
		memset(adapter->vfinfo[vf].vf_mac_addresses, 0, ETH_ALEN);

	return retval;
}