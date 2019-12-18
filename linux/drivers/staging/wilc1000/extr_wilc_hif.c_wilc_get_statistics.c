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
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wid {int size; int /*<<< orphan*/ * val; void* type; int /*<<< orphan*/  id; } ;
struct rf_info {scalar_t__ link_speed; int /*<<< orphan*/  tx_fail_cnt; int /*<<< orphan*/  rx_cnt; int /*<<< orphan*/  tx_cnt; int /*<<< orphan*/  rssi; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 scalar_t__ DEFAULT_LINK_SPEED ; 
 scalar_t__ TCP_ACK_FILTER_LINK_SPEED_THRESH ; 
 void* WID_CHAR ; 
 int /*<<< orphan*/  WID_FAILED_COUNT ; 
 void* WID_INT ; 
 int /*<<< orphan*/  WID_LINKSPEED ; 
 int /*<<< orphan*/  WID_RECEIVED_FRAGMENT_COUNT ; 
 int /*<<< orphan*/  WID_RSSI ; 
 int /*<<< orphan*/  WID_SUCCESS_FRAME_COUNT ; 
 int /*<<< orphan*/  WILC_GET_CFG ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wilc_enable_tcp_ack_filter (struct wilc_vif*,int) ; 
 size_t wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,size_t) ; 

int wilc_get_statistics(struct wilc_vif *vif, struct rf_info *stats)
{
	struct wid wid_list[5];
	u32 wid_cnt = 0, result;

	wid_list[wid_cnt].id = WID_LINKSPEED;
	wid_list[wid_cnt].type = WID_CHAR;
	wid_list[wid_cnt].size = sizeof(char);
	wid_list[wid_cnt].val = (s8 *)&stats->link_speed;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_RSSI;
	wid_list[wid_cnt].type = WID_CHAR;
	wid_list[wid_cnt].size = sizeof(char);
	wid_list[wid_cnt].val = (s8 *)&stats->rssi;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_SUCCESS_FRAME_COUNT;
	wid_list[wid_cnt].type = WID_INT;
	wid_list[wid_cnt].size = sizeof(u32);
	wid_list[wid_cnt].val = (s8 *)&stats->tx_cnt;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_RECEIVED_FRAGMENT_COUNT;
	wid_list[wid_cnt].type = WID_INT;
	wid_list[wid_cnt].size = sizeof(u32);
	wid_list[wid_cnt].val = (s8 *)&stats->rx_cnt;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_FAILED_COUNT;
	wid_list[wid_cnt].type = WID_INT;
	wid_list[wid_cnt].size = sizeof(u32);
	wid_list[wid_cnt].val = (s8 *)&stats->tx_fail_cnt;
	wid_cnt++;

	result = wilc_send_config_pkt(vif, WILC_GET_CFG, wid_list, wid_cnt);
	if (result) {
		netdev_err(vif->ndev, "Failed to send scan parameters\n");
		return result;
	}

	if (stats->link_speed > TCP_ACK_FILTER_LINK_SPEED_THRESH &&
	    stats->link_speed != DEFAULT_LINK_SPEED)
		wilc_enable_tcp_ack_filter(vif, true);
	else if (stats->link_speed != DEFAULT_LINK_SPEED)
		wilc_enable_tcp_ack_filter(vif, false);

	return result;
}