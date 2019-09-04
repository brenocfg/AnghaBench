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
typedef  int u16 ;
struct hclgevf_dev {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int BIT (int) ; 
 int BITS_PER_BYTE ; 
 int DIV_ROUND_UP (int,int) ; 
 int HCLGEVF_MTA_TBL_SIZE ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_MTA_STATUS_UPDATE ; 
 int /*<<< orphan*/  HCLGE_MBX_SET_MULTICAST ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static int hclgevf_do_update_mta_status(struct hclgevf_dev *hdev,
					unsigned long *status)
{
#define HCLGEVF_MTA_STATUS_MSG_SIZE 13
#define HCLGEVF_MTA_STATUS_MSG_BITS \
			(HCLGEVF_MTA_STATUS_MSG_SIZE * BITS_PER_BYTE)
#define HCLGEVF_MTA_STATUS_MSG_END_BITS \
			(HCLGEVF_MTA_TBL_SIZE % HCLGEVF_MTA_STATUS_MSG_BITS)
	u16 tbl_cnt;
	u16 tbl_idx;
	u8 msg_cnt;
	u8 msg_idx;
	int ret;

	msg_cnt = DIV_ROUND_UP(HCLGEVF_MTA_TBL_SIZE,
			       HCLGEVF_MTA_STATUS_MSG_BITS);
	tbl_idx = 0;
	msg_idx = 0;
	while (msg_cnt--) {
		u8 msg[HCLGEVF_MTA_STATUS_MSG_SIZE + 1];
		u8 *p = &msg[1];
		u8 msg_ofs;
		u8 msg_bit;

		memset(msg, 0, sizeof(msg));

		/* set index field */
		msg[0] = 0x7F & msg_idx;

		/* set end flag field */
		if (msg_cnt == 0) {
			msg[0] |= 0x80;
			tbl_cnt = HCLGEVF_MTA_STATUS_MSG_END_BITS;
		} else {
			tbl_cnt = HCLGEVF_MTA_STATUS_MSG_BITS;
		}

		/* set status field */
		msg_ofs = 0;
		msg_bit = 0;
		while (tbl_cnt--) {
			if (test_bit(tbl_idx, status))
				p[msg_ofs] |= BIT(msg_bit);

			tbl_idx++;

			msg_bit++;
			if (msg_bit == BITS_PER_BYTE) {
				msg_bit = 0;
				msg_ofs++;
			}
		}

		ret = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_MULTICAST,
					   HCLGE_MBX_MAC_VLAN_MTA_STATUS_UPDATE,
					   msg, sizeof(msg), false, NULL, 0);
		if (ret)
			break;

		msg_idx++;
	}

	return ret;
}