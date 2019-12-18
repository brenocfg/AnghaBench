#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sk_buff {scalar_t__ head; } ;
struct l2t_entry {int vlan; } ;
struct fw_flowc_wr {TYPE_1__* mnemval; void* flowid_len16; void* op_to_nparams; } ;
struct cxgbi_sock {int tx_chan; int rss_qid; int snd_nxt; int rcv_nxt; int snd_win; int advmss; size_t port_id; TYPE_2__* cdev; int /*<<< orphan*/  tid; scalar_t__ l2t; } ;
struct TYPE_4__ {int pfvf; int /*<<< orphan*/ * ports; } ;
struct TYPE_3__ {int val; scalar_t__ mnemonic; } ;

/* Variables and functions */
 int CPL_L2T_VLAN_NONE ; 
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 scalar_t__ FW_FLOWC_MNEM_CH ; 
 scalar_t__ FW_FLOWC_MNEM_DCBPRIO ; 
 scalar_t__ FW_FLOWC_MNEM_IQID ; 
 scalar_t__ FW_FLOWC_MNEM_MSS ; 
 scalar_t__ FW_FLOWC_MNEM_PFNVFN ; 
 scalar_t__ FW_FLOWC_MNEM_PORT ; 
 scalar_t__ FW_FLOWC_MNEM_RCVNXT ; 
 scalar_t__ FW_FLOWC_MNEM_SNDBUF ; 
 scalar_t__ FW_FLOWC_MNEM_SNDNXT ; 
 scalar_t__ FW_FLOWC_MNEM_TXDATAPLEN_MAX ; 
 int /*<<< orphan*/  FW_FLOWC_WR ; 
 int FW_FLOWC_WR_NPARAMS_V (int) ; 
 int FW_WR_FLOWID_V (int /*<<< orphan*/ ) ; 
 int FW_WR_LEN16_V (int) ; 
 int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int VLAN_PRIO_MASK ; 
 int VLAN_PRIO_SHIFT ; 
 struct sk_buff* alloc_wr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,size_t) ; 
 int tx_flowc_wr_credits (int*,int*) ; 

__attribute__((used)) static inline int send_tx_flowc_wr(struct cxgbi_sock *csk)
{
	struct sk_buff *skb;
	struct fw_flowc_wr *flowc;
	int nparams, flowclen16, flowclen;

#ifdef CONFIG_CHELSIO_T4_DCB
	u16 vlan = ((struct l2t_entry *)csk->l2t)->vlan;
#endif
	flowclen16 = tx_flowc_wr_credits(&nparams, &flowclen);
	skb = alloc_wr(flowclen, 0, GFP_ATOMIC);
	flowc = (struct fw_flowc_wr *)skb->head;
	flowc->op_to_nparams =
		htonl(FW_WR_OP_V(FW_FLOWC_WR) | FW_FLOWC_WR_NPARAMS_V(nparams));
	flowc->flowid_len16 =
		htonl(FW_WR_LEN16_V(flowclen16) | FW_WR_FLOWID_V(csk->tid));
	flowc->mnemval[0].mnemonic = FW_FLOWC_MNEM_PFNVFN;
	flowc->mnemval[0].val = htonl(csk->cdev->pfvf);
	flowc->mnemval[1].mnemonic = FW_FLOWC_MNEM_CH;
	flowc->mnemval[1].val = htonl(csk->tx_chan);
	flowc->mnemval[2].mnemonic = FW_FLOWC_MNEM_PORT;
	flowc->mnemval[2].val = htonl(csk->tx_chan);
	flowc->mnemval[3].mnemonic = FW_FLOWC_MNEM_IQID;
	flowc->mnemval[3].val = htonl(csk->rss_qid);
	flowc->mnemval[4].mnemonic = FW_FLOWC_MNEM_SNDNXT;
	flowc->mnemval[4].val = htonl(csk->snd_nxt);
	flowc->mnemval[5].mnemonic = FW_FLOWC_MNEM_RCVNXT;
	flowc->mnemval[5].val = htonl(csk->rcv_nxt);
	flowc->mnemval[6].mnemonic = FW_FLOWC_MNEM_SNDBUF;
	flowc->mnemval[6].val = htonl(csk->snd_win);
	flowc->mnemval[7].mnemonic = FW_FLOWC_MNEM_MSS;
	flowc->mnemval[7].val = htonl(csk->advmss);
	flowc->mnemval[8].mnemonic = 0;
	flowc->mnemval[8].val = 0;
	flowc->mnemval[8].mnemonic = FW_FLOWC_MNEM_TXDATAPLEN_MAX;
	flowc->mnemval[8].val = 16384;
#ifdef CONFIG_CHELSIO_T4_DCB
	flowc->mnemval[9].mnemonic = FW_FLOWC_MNEM_DCBPRIO;
	if (vlan == CPL_L2T_VLAN_NONE) {
		pr_warn_ratelimited("csk %u without VLAN Tag on DCB Link\n",
				    csk->tid);
		flowc->mnemval[9].val = cpu_to_be32(0);
	} else {
		flowc->mnemval[9].val = cpu_to_be32((vlan & VLAN_PRIO_MASK) >>
					VLAN_PRIO_SHIFT);
	}
#endif

	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p, tid 0x%x, %u,%u,%u,%u,%u,%u,%u.\n",
		csk, csk->tid, 0, csk->tx_chan, csk->rss_qid,
		csk->snd_nxt, csk->rcv_nxt, csk->snd_win,
		csk->advmss);

	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);

	return flowclen16;
}