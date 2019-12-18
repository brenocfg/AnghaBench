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
typedef  int u32 ;
struct cudbg_ver_hdr {int dummy; } ;
struct cudbg_qdesc_info {int dummy; } ;
struct cudbg_qdesc_entry {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CXGB4_TX_MAX ; 
 int CXGB4_ULD_MAX ; 
 int INGQ_EXTRAS ; 
 int MAX_CTRL_QUEUES ; 
 int MAX_CTRL_TXQ_DESC_SIZE ; 
 int MAX_CTRL_TXQ_ENTRIES ; 
 int MAX_ETH_QSETS ; 
 int MAX_FL_DESC_SIZE ; 
 int MAX_OFLD_QSETS ; 
 int MAX_RSPQ_ENTRIES ; 
 int MAX_RXQ_DESC_SIZE ; 
 int MAX_RX_BUFFERS ; 
 int MAX_TXQ_DESC_SIZE ; 
 int MAX_TXQ_ENTRIES ; 
 int MAX_ULD_QSETS ; 
 int SGE_MAX_IQ_SIZE ; 

void cudbg_fill_qdesc_num_and_size(const struct adapter *padap,
				   u32 *num, u32 *size)
{
	u32 tot_entries = 0, tot_size = 0;

	/* NIC TXQ, RXQ, FLQ, and CTRLQ */
	tot_entries += MAX_ETH_QSETS * 3;
	tot_entries += MAX_CTRL_QUEUES;

	tot_size += MAX_ETH_QSETS * MAX_TXQ_ENTRIES * MAX_TXQ_DESC_SIZE;
	tot_size += MAX_ETH_QSETS * MAX_RSPQ_ENTRIES * MAX_RXQ_DESC_SIZE;
	tot_size += MAX_ETH_QSETS * MAX_RX_BUFFERS * MAX_FL_DESC_SIZE;
	tot_size += MAX_CTRL_QUEUES * MAX_CTRL_TXQ_ENTRIES *
		    MAX_CTRL_TXQ_DESC_SIZE;

	/* FW_EVTQ and INTRQ */
	tot_entries += INGQ_EXTRAS;
	tot_size += INGQ_EXTRAS * MAX_RSPQ_ENTRIES * MAX_RXQ_DESC_SIZE;

	/* PTP_TXQ */
	tot_entries += 1;
	tot_size += MAX_TXQ_ENTRIES * MAX_TXQ_DESC_SIZE;

	/* ULD TXQ, RXQ, and FLQ */
	tot_entries += CXGB4_TX_MAX * MAX_OFLD_QSETS;
	tot_entries += CXGB4_ULD_MAX * MAX_ULD_QSETS * 2;

	tot_size += CXGB4_TX_MAX * MAX_OFLD_QSETS * MAX_TXQ_ENTRIES *
		    MAX_TXQ_DESC_SIZE;
	tot_size += CXGB4_ULD_MAX * MAX_ULD_QSETS * MAX_RSPQ_ENTRIES *
		    MAX_RXQ_DESC_SIZE;
	tot_size += CXGB4_ULD_MAX * MAX_ULD_QSETS * MAX_RX_BUFFERS *
		    MAX_FL_DESC_SIZE;

	/* ULD CIQ */
	tot_entries += CXGB4_ULD_MAX * MAX_ULD_QSETS;
	tot_size += CXGB4_ULD_MAX * MAX_ULD_QSETS * SGE_MAX_IQ_SIZE *
		    MAX_RXQ_DESC_SIZE;

	tot_size += sizeof(struct cudbg_ver_hdr) +
		    sizeof(struct cudbg_qdesc_info) +
		    sizeof(struct cudbg_qdesc_entry) * tot_entries;

	if (num)
		*num = tot_entries;

	if (size)
		*size = tot_size;
}