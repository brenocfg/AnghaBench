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
typedef  int /*<<< orphan*/  u32 ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wid {int size; int /*<<< orphan*/ * val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WID_GET_INACTIVE_TIME ; 
 int /*<<< orphan*/  WID_INT ; 
 int /*<<< orphan*/  WID_SET_STA_MAC_INACTIVE_TIME ; 
 int /*<<< orphan*/  WID_STR ; 
 int /*<<< orphan*/  WILC_GET_CFG ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

s32 wilc_get_inactive_time(struct wilc_vif *vif, const u8 *mac, u32 *out_val)
{
	struct wid wid;
	s32 result;

	wid.id = WID_SET_STA_MAC_INACTIVE_TIME;
	wid.type = WID_STR;
	wid.size = ETH_ALEN;
	wid.val = kzalloc(wid.size, GFP_KERNEL);
	if (!wid.val)
		return -ENOMEM;

	ether_addr_copy(wid.val, mac);
	result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	kfree(wid.val);
	if (result) {
		netdev_err(vif->ndev, "Failed to set inactive mac\n");
		return result;
	}

	wid.id = WID_GET_INACTIVE_TIME;
	wid.type = WID_INT;
	wid.val = (s8 *)out_val;
	wid.size = sizeof(u32);
	result = wilc_send_config_pkt(vif, WILC_GET_CFG, &wid, 1);
	if (result)
		netdev_err(vif->ndev, "Failed to get inactive time\n");

	return result;
}