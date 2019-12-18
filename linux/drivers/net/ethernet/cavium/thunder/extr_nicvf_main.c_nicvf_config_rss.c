#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tbl_offset; int tbl_len; int /*<<< orphan*/ * ind_tbl; int /*<<< orphan*/  msg; int /*<<< orphan*/  hash_bits; int /*<<< orphan*/  vf_id; } ;
union nic_mbx {TYPE_1__ rss_cfg; } ;
struct nicvf_rss_info {int rss_size; int /*<<< orphan*/ * ind_tbl; int /*<<< orphan*/  hash_bits; } ;
struct nicvf {int /*<<< orphan*/  vf_id; struct nicvf_rss_info rss_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_RSS_CFG ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_RSS_CFG_CONT ; 
 int /*<<< orphan*/  RSS_IND_TBL_LEN_PER_MBX_MSG ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

void nicvf_config_rss(struct nicvf *nic)
{
	union nic_mbx mbx = {};
	struct nicvf_rss_info *rss = &nic->rss_info;
	int ind_tbl_len = rss->rss_size;
	int i, nextq = 0;

	mbx.rss_cfg.vf_id = nic->vf_id;
	mbx.rss_cfg.hash_bits = rss->hash_bits;
	while (ind_tbl_len) {
		mbx.rss_cfg.tbl_offset = nextq;
		mbx.rss_cfg.tbl_len = min(ind_tbl_len,
					       RSS_IND_TBL_LEN_PER_MBX_MSG);
		mbx.rss_cfg.msg = mbx.rss_cfg.tbl_offset ?
			  NIC_MBOX_MSG_RSS_CFG_CONT : NIC_MBOX_MSG_RSS_CFG;

		for (i = 0; i < mbx.rss_cfg.tbl_len; i++)
			mbx.rss_cfg.ind_tbl[i] = rss->ind_tbl[nextq++];

		nicvf_send_msg_to_pf(nic, &mbx);

		ind_tbl_len -= mbx.rss_cfg.tbl_len;
	}
}