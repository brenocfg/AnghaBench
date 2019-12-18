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
struct sk_buff {int dummy; } ;
struct cxgbit_iso_info {int flags; int len; int /*<<< orphan*/  burst_len; int /*<<< orphan*/  mpdu; } ;
struct cpl_tx_data_iso {scalar_t__ reserved3; void* buffer_offset; void* datasn_offset; void* reserved2_seglen_offset; void* len; void* burst_size; int /*<<< orphan*/  mpdu; scalar_t__ ahs_len; void* op_to_scsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_TX_DATA_ISO ; 
 int CPL_TX_DATA_ISO_CPLHDRLEN_V (int /*<<< orphan*/ ) ; 
 int CPL_TX_DATA_ISO_FIRST_V (unsigned int) ; 
 int CPL_TX_DATA_ISO_HDRCRC_V (unsigned int) ; 
 int CPL_TX_DATA_ISO_IMMEDIATE_V (int /*<<< orphan*/ ) ; 
 int CPL_TX_DATA_ISO_LAST_V (unsigned int) ; 
 int CPL_TX_DATA_ISO_OP_V (int /*<<< orphan*/ ) ; 
 int CPL_TX_DATA_ISO_PLDCRC_V (unsigned int) ; 
 int CPL_TX_DATA_ISO_SCSI_V (int) ; 
 int CXGBIT_ISO_FSLICE ; 
 int CXGBIT_ISO_LSLICE ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 struct cpl_tx_data_iso* __skb_push (struct sk_buff*,int) ; 
 unsigned int cxgbit_skcb_submode (struct sk_buff*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static void
cxgbit_cpl_tx_data_iso(struct sk_buff *skb, struct cxgbit_iso_info *iso_info)
{
	struct cpl_tx_data_iso *cpl;
	unsigned int submode = cxgbit_skcb_submode(skb);
	unsigned int fslice = !!(iso_info->flags & CXGBIT_ISO_FSLICE);
	unsigned int lslice = !!(iso_info->flags & CXGBIT_ISO_LSLICE);

	cpl = __skb_push(skb, sizeof(*cpl));

	cpl->op_to_scsi = htonl(CPL_TX_DATA_ISO_OP_V(CPL_TX_DATA_ISO) |
			CPL_TX_DATA_ISO_FIRST_V(fslice) |
			CPL_TX_DATA_ISO_LAST_V(lslice) |
			CPL_TX_DATA_ISO_CPLHDRLEN_V(0) |
			CPL_TX_DATA_ISO_HDRCRC_V(submode & 1) |
			CPL_TX_DATA_ISO_PLDCRC_V(((submode >> 1) & 1)) |
			CPL_TX_DATA_ISO_IMMEDIATE_V(0) |
			CPL_TX_DATA_ISO_SCSI_V(2));

	cpl->ahs_len = 0;
	cpl->mpdu = htons(DIV_ROUND_UP(iso_info->mpdu, 4));
	cpl->burst_size = htonl(DIV_ROUND_UP(iso_info->burst_len, 4));
	cpl->len = htonl(iso_info->len);
	cpl->reserved2_seglen_offset = htonl(0);
	cpl->datasn_offset = htonl(0);
	cpl->buffer_offset = htonl(0);
	cpl->reserved3 = 0;

	__skb_pull(skb, sizeof(*cpl));
}