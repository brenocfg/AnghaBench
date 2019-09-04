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
struct vxge_vpath {scalar_t__ mac_addr_cnt; int /*<<< orphan*/  mcast_addr_cnt; int /*<<< orphan*/  mac_addr_list; } ;
struct vxge_mac_addrs {int /*<<< orphan*/  state; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  item; } ;
struct macInfo {int /*<<< orphan*/  macaddr; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int FALSE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int TRUE ; 
 int /*<<< orphan*/  VXGE_DRIVER_NAME ; 
 int /*<<< orphan*/  VXGE_ERR ; 
 scalar_t__ VXGE_MAX_LEARN_MAC_ADDR_CNT ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 struct vxge_mac_addrs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_debug_mem (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxge_mac_list_add(struct vxge_vpath *vpath, struct macInfo *mac)
{
	struct vxge_mac_addrs *new_mac_entry;
	u8 *mac_address = NULL;

	if (vpath->mac_addr_cnt >= VXGE_MAX_LEARN_MAC_ADDR_CNT)
		return TRUE;

	new_mac_entry = kzalloc(sizeof(struct vxge_mac_addrs), GFP_ATOMIC);
	if (!new_mac_entry) {
		vxge_debug_mem(VXGE_ERR,
			"%s: memory allocation failed",
			VXGE_DRIVER_NAME);
		return FALSE;
	}

	list_add(&new_mac_entry->item, &vpath->mac_addr_list);

	/* Copy the new mac address to the list */
	mac_address = (u8 *)&new_mac_entry->macaddr;
	memcpy(mac_address, mac->macaddr, ETH_ALEN);

	new_mac_entry->state = mac->state;
	vpath->mac_addr_cnt++;

	if (is_multicast_ether_addr(mac->macaddr))
		vpath->mcast_addr_cnt++;

	return TRUE;
}