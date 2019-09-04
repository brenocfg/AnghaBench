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
typedef  size_t u8 ;
typedef  int u16 ;
struct hclge_vport {int dummy; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 int BITS_PER_BYTE ; 
 int BITS_TO_LONGS (int) ; 
 int HCLGE_MTA_TBL_SIZE ; 
 int hclge_update_mta_status_common (struct hclge_vport*,unsigned long*,size_t,int,int) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

__attribute__((used)) static int hclge_set_vf_mc_mta_status(struct hclge_vport *vport,
				      u8 *msg, u8 idx, bool is_end)
{
#define HCLGE_MTA_STATUS_MSG_SIZE 13
#define HCLGE_MTA_STATUS_MSG_BITS \
				(HCLGE_MTA_STATUS_MSG_SIZE * BITS_PER_BYTE)
#define HCLGE_MTA_STATUS_MSG_END_BITS \
				(HCLGE_MTA_TBL_SIZE % HCLGE_MTA_STATUS_MSG_BITS)
	unsigned long status[BITS_TO_LONGS(HCLGE_MTA_STATUS_MSG_BITS)];
	u16 tbl_cnt;
	u16 tbl_idx;
	u8 msg_ofs;
	u8 msg_bit;

	tbl_cnt = is_end ? HCLGE_MTA_STATUS_MSG_END_BITS :
			HCLGE_MTA_STATUS_MSG_BITS;

	/* set msg field */
	msg_ofs = 0;
	msg_bit = 0;
	memset(status, 0, sizeof(status));
	for (tbl_idx = 0; tbl_idx < tbl_cnt; tbl_idx++) {
		if (msg[msg_ofs] & BIT(msg_bit))
			set_bit(tbl_idx, status);

		msg_bit++;
		if (msg_bit == BITS_PER_BYTE) {
			msg_bit = 0;
			msg_ofs++;
		}
	}

	return hclge_update_mta_status_common(vport,
					status, idx * HCLGE_MTA_STATUS_MSG_BITS,
					tbl_cnt, is_end);
}