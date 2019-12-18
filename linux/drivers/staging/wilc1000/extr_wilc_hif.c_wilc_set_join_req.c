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
struct wilc_vif {struct host_if_drv* hif_drv; } ;
struct wilc_conn_info {size_t req_ies_len; int /*<<< orphan*/  req_ies; int /*<<< orphan*/  bssid; } ;
struct host_if_drv {int /*<<< orphan*/  connect_timer; struct wilc_vif* connect_timer_vif; struct wilc_conn_info conn_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WILC_HIF_CONNECT_TIMEOUT_MS ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wilc_send_connect_wid (struct wilc_vif*) ; 

int wilc_set_join_req(struct wilc_vif *vif, u8 *bssid, const u8 *ies,
		      size_t ies_len)
{
	int result;
	struct host_if_drv *hif_drv = vif->hif_drv;
	struct wilc_conn_info *conn_info = &hif_drv->conn_info;

	if (bssid)
		ether_addr_copy(conn_info->bssid, bssid);

	if (ies) {
		conn_info->req_ies_len = ies_len;
		conn_info->req_ies = kmemdup(ies, ies_len, GFP_KERNEL);
		if (!conn_info->req_ies)
			return -ENOMEM;
	}

	result = wilc_send_connect_wid(vif);
	if (result)
		goto free_ies;

	hif_drv->connect_timer_vif = vif;
	mod_timer(&hif_drv->connect_timer,
		  jiffies + msecs_to_jiffies(WILC_HIF_CONNECT_TIMEOUT_MS));

	return 0;

free_ies:
	kfree(conn_info->req_ies);

	return result;
}