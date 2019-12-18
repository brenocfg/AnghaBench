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
struct wilc_cfg_rsp {int seq_no; scalar_t__ type; } ;
struct wilc {int dummy; } ;

/* Variables and functions */
 scalar_t__ WILC_CFG_RSP ; 
 scalar_t__ WILC_CFG_RSP_STATUS ; 
 int /*<<< orphan*/  wilc_gnrl_async_info_received (struct wilc*,int*,int) ; 
 int /*<<< orphan*/  wilc_network_info_received (struct wilc*,int*,int) ; 
 int /*<<< orphan*/  wilc_scan_complete_received (struct wilc*,int*,int) ; 
 int /*<<< orphan*/  wilc_wlan_parse_info_frame (struct wilc*,int*) ; 
 int /*<<< orphan*/  wilc_wlan_parse_response_frame (struct wilc*,int*,int) ; 

void wilc_wlan_cfg_indicate_rx(struct wilc *wilc, u8 *frame, int size,
			       struct wilc_cfg_rsp *rsp)
{
	u8 msg_type;
	u8 msg_id;

	msg_type = frame[0];
	msg_id = frame[1];      /* seq no */
	frame += 4;
	size -= 4;
	rsp->type = 0;

	/*
	 * The valid types of response messages are
	 * 'R' (Response),
	 * 'I' (Information), and
	 * 'N' (Network Information)
	 */

	switch (msg_type) {
	case 'R':
		wilc_wlan_parse_response_frame(wilc, frame, size);
		rsp->type = WILC_CFG_RSP;
		rsp->seq_no = msg_id;
		break;

	case 'I':
		wilc_wlan_parse_info_frame(wilc, frame);
		rsp->type = WILC_CFG_RSP_STATUS;
		rsp->seq_no = msg_id;
		/*call host interface info parse as well*/
		wilc_gnrl_async_info_received(wilc, frame - 4, size + 4);
		break;

	case 'N':
		wilc_network_info_received(wilc, frame - 4, size + 4);
		break;

	case 'S':
		wilc_scan_complete_received(wilc, frame - 4, size + 4);
		break;

	default:
		rsp->seq_no = msg_id;
		break;
	}
}