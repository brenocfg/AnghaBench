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
struct fw_filter_wr {int /*<<< orphan*/  rx_chan_rx_rpl_iq; void* del_filter_to_l2tix; void* tid_to_iq; void* len16_pkd; void* op_pkd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FILTER_WR ; 
 int FW_FILTER_WR_DEL_FILTER_F ; 
 int FW_FILTER_WR_NOREPLY_V (int) ; 
 int /*<<< orphan*/  FW_FILTER_WR_RX_RPL_IQ_V (int) ; 
 int FW_FILTER_WR_TID_V (unsigned int) ; 
 int FW_WR_LEN16_V (int) ; 
 int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_filter_wr*,int /*<<< orphan*/ ,int) ; 

void t4_mk_filtdelwr(unsigned int ftid, struct fw_filter_wr *wr, int qid)
{
	memset(wr, 0, sizeof(*wr));
	wr->op_pkd = cpu_to_be32(FW_WR_OP_V(FW_FILTER_WR));
	wr->len16_pkd = cpu_to_be32(FW_WR_LEN16_V(sizeof(*wr) / 16));
	wr->tid_to_iq = cpu_to_be32(FW_FILTER_WR_TID_V(ftid) |
				    FW_FILTER_WR_NOREPLY_V(qid < 0));
	wr->del_filter_to_l2tix = cpu_to_be32(FW_FILTER_WR_DEL_FILTER_F);
	if (qid >= 0)
		wr->rx_chan_rx_rpl_iq =
			cpu_to_be16(FW_FILTER_WR_RX_RPL_IQ_V(qid));
}