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
struct sk_buff {int dummy; } ;
struct cxgbit_lro_pdu_cb {int flags; int complete; scalar_t__ pdulen; int /*<<< orphan*/  ddigest; } ;
struct cxgbit_lro_cb {int complete; int /*<<< orphan*/  pdu_idx; int /*<<< orphan*/  pdu_totallen; int /*<<< orphan*/  csk; } ;
struct cpl_rx_iscsi_ddp {int /*<<< orphan*/  len; int /*<<< orphan*/  ulp_crc; int /*<<< orphan*/  ddpvld; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int PDUCBF_RX_HDR ; 
 int PDUCBF_RX_STATUS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbit_process_ddpvld (int /*<<< orphan*/ ,struct cxgbit_lro_pdu_cb*,int /*<<< orphan*/ ) ; 
 struct cxgbit_lro_cb* cxgbit_skb_lro_cb (struct sk_buff*) ; 
 struct cxgbit_lro_pdu_cb* cxgbit_skb_lro_pdu_cb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cxgbit_lro_add_packet_rsp(struct sk_buff *skb, u8 op, const __be64 *rsp)
{
	struct cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	struct cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb,
						lro_cb->pdu_idx);
	struct cpl_rx_iscsi_ddp *cpl = (struct cpl_rx_iscsi_ddp *)(rsp + 1);

	cxgbit_process_ddpvld(lro_cb->csk, pdu_cb, be32_to_cpu(cpl->ddpvld));

	pdu_cb->flags |= PDUCBF_RX_STATUS;
	pdu_cb->ddigest = ntohl(cpl->ulp_crc);
	pdu_cb->pdulen = ntohs(cpl->len);

	if (pdu_cb->flags & PDUCBF_RX_HDR)
		pdu_cb->complete = true;

	lro_cb->pdu_totallen += pdu_cb->pdulen;
	lro_cb->complete = true;
	lro_cb->pdu_idx++;
}