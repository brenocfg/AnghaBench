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
struct wid {int /*<<< orphan*/ * val; scalar_t__ size; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct station_parameters {scalar_t__ supported_rates_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WID_ADD_STA ; 
 int /*<<< orphan*/  WID_BIN ; 
 scalar_t__ WILC_ADD_STA_LENGTH ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wilc_hif_pack_sta_param (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,struct station_parameters*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_add_station(struct wilc_vif *vif, const u8 *mac,
		     struct station_parameters *params)
{
	struct wid wid;
	int result;
	u8 *cur_byte;

	wid.id = WID_ADD_STA;
	wid.type = WID_BIN;
	wid.size = WILC_ADD_STA_LENGTH + params->supported_rates_len;
	wid.val = kmalloc(wid.size, GFP_KERNEL);
	if (!wid.val)
		return -ENOMEM;

	cur_byte = wid.val;
	wilc_hif_pack_sta_param(cur_byte, mac, params);

	result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	if (result != 0)
		netdev_err(vif->ndev, "Failed to send add station\n");

	kfree(wid.val);

	return result;
}