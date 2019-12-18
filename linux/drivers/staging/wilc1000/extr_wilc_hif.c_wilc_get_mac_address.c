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
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wid {int /*<<< orphan*/ * val; int /*<<< orphan*/  size; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WID_MAC_ADDR ; 
 int /*<<< orphan*/  WID_STR ; 
 int /*<<< orphan*/  WILC_GET_CFG ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_get_mac_address(struct wilc_vif *vif, u8 *mac_addr)
{
	int result;
	struct wid wid;

	wid.id = WID_MAC_ADDR;
	wid.type = WID_STR;
	wid.size = ETH_ALEN;
	wid.val = mac_addr;

	result = wilc_send_config_pkt(vif, WILC_GET_CFG, &wid, 1);
	if (result)
		netdev_err(vif->ndev, "Failed to get mac address\n");

	return result;
}