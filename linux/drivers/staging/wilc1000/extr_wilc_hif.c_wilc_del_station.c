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
struct wid {int /*<<< orphan*/  val; int /*<<< orphan*/  size; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WID_BIN ; 
 int /*<<< orphan*/  WID_REMOVE_STA ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_del_station(struct wilc_vif *vif, const u8 *mac_addr)
{
	struct wid wid;
	int result;

	wid.id = WID_REMOVE_STA;
	wid.type = WID_BIN;
	wid.size = ETH_ALEN;
	wid.val = kzalloc(wid.size, GFP_KERNEL);
	if (!wid.val)
		return -ENOMEM;

	if (!mac_addr)
		eth_broadcast_addr(wid.val);
	else
		ether_addr_copy(wid.val, mac_addr);

	result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	if (result)
		netdev_err(vif->ndev, "Failed to del station\n");

	kfree(wid.val);

	return result;
}