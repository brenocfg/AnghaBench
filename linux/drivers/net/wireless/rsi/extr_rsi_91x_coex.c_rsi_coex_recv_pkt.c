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
typedef  int u8 ;
struct rsi_common {int hibernate_resume; } ;

/* Variables and functions */
#define  COMMON_CARD_READY_IND 129 
 int /*<<< orphan*/  INFO_ZONE ; 
 size_t RSI_RX_DESC_MSG_TYPE_OFFSET ; 
#define  SLEEP_NOTIFY_IND 128 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_handle_card_ready (struct rsi_common*,int*) ; 
 int /*<<< orphan*/  rsi_mgmt_pkt_recv (struct rsi_common*,int*) ; 

int rsi_coex_recv_pkt(struct rsi_common *common, u8 *msg)
{
	u8 msg_type = msg[RSI_RX_DESC_MSG_TYPE_OFFSET];

	switch (msg_type) {
	case COMMON_CARD_READY_IND:
		rsi_dbg(INFO_ZONE, "common card ready received\n");
		common->hibernate_resume = false;
		rsi_handle_card_ready(common, msg);
		break;
	case SLEEP_NOTIFY_IND:
		rsi_dbg(INFO_ZONE, "sleep notify received\n");
		rsi_mgmt_pkt_recv(common, msg);
		break;
	}

	return 0;
}