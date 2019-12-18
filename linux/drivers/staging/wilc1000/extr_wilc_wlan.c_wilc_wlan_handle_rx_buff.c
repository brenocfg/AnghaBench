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
typedef  int u32 ;
struct wilc_cfg_rsp {scalar_t__ type; scalar_t__ seq_no; } ;
struct wilc {scalar_t__ cfg_seq_no; int /*<<< orphan*/  cfg_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_HDR_OFFSET ; 
 int IS_MANAGMEMENT ; 
 scalar_t__ WILC_CFG_RSP ; 
 scalar_t__ WILC_CFG_RSP_STATUS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wilc_frmw_to_host (struct wilc*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wilc_mac_indicate (struct wilc*) ; 
 int /*<<< orphan*/  wilc_wfi_mgmt_rx (struct wilc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wilc_wlan_cfg_indicate_rx (struct wilc*,int /*<<< orphan*/ *,int,struct wilc_cfg_rsp*) ; 

__attribute__((used)) static void wilc_wlan_handle_rx_buff(struct wilc *wilc, u8 *buffer, int size)
{
	int offset = 0;
	u32 header;
	u32 pkt_len, pkt_offset, tp_len;
	int is_cfg_packet;
	u8 *buff_ptr;

	do {
		buff_ptr = buffer + offset;
		header = get_unaligned_le32(buff_ptr);

		is_cfg_packet = (header >> 31) & 0x1;
		pkt_offset = (header >> 22) & 0x1ff;
		tp_len = (header >> 11) & 0x7ff;
		pkt_len = header & 0x7ff;

		if (pkt_len == 0 || tp_len == 0)
			break;

		if (pkt_offset & IS_MANAGMEMENT) {
			buff_ptr += HOST_HDR_OFFSET;
			wilc_wfi_mgmt_rx(wilc, buff_ptr, pkt_len);
		} else {
			if (!is_cfg_packet) {
				if (pkt_len > 0) {
					wilc_frmw_to_host(wilc, buff_ptr,
							  pkt_len, pkt_offset);
				}
			} else {
				struct wilc_cfg_rsp rsp;

				buff_ptr += pkt_offset;

				wilc_wlan_cfg_indicate_rx(wilc, buff_ptr,
							  pkt_len,
							  &rsp);
				if (rsp.type == WILC_CFG_RSP) {
					if (wilc->cfg_seq_no == rsp.seq_no)
						complete(&wilc->cfg_event);
				} else if (rsp.type == WILC_CFG_RSP_STATUS) {
					wilc_mac_indicate(wilc);
				}
			}
		}
		offset += tp_len;
		if (offset >= size)
			break;
	} while (1);
}