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
typedef  int /*<<< orphan*/  u32 ;
struct tid_info {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * function; } ;
struct cxgbi_sock {unsigned int atid; scalar_t__ state; unsigned int tid; int rcv_win; int advmss; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  rcv_wup; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  copied_seq; TYPE_1__ retry_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  csk_family; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct cxgbi_device {int /*<<< orphan*/  owner; } ;
struct cxgb4_lld_info {int* mtus; struct tid_info* tids; } ;
struct cpl_act_establish {int /*<<< orphan*/  tcp_opt; int /*<<< orphan*/  snd_isn; int /*<<< orphan*/  rcv_isn; int /*<<< orphan*/  tos_atid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_ACTIVE_CLOSE_NEEDED ; 
 int /*<<< orphan*/  CTPF_HAS_TID ; 
 scalar_t__ CTP_ACTIVE_OPEN ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 unsigned int GET_TID (struct cpl_act_establish*) ; 
 int RCV_BUFSIZ_MASK ; 
 size_t TCPOPT_MSS_G (unsigned short) ; 
 scalar_t__ TCPOPT_TSTAMP_G (unsigned short) ; 
 unsigned int TID_TID_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_insert_tid (struct tid_info*,struct cxgbi_sock*,unsigned int,int /*<<< orphan*/ ) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgbi_conn_tx_open (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_established (struct cxgbi_sock*,int /*<<< orphan*/ ,unsigned short) ; 
 int cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  free_atid (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,size_t,int) ; 
 struct cxgbi_sock* lookup_atid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,...) ; 
 int /*<<< orphan*/  pr_info (char*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_info_ipaddr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_tx_frames (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_abort_req (struct cxgbi_sock*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_act_establish(struct cxgbi_device *cdev, struct sk_buff *skb)
{
	struct cxgbi_sock *csk;
	struct cpl_act_establish *req = (struct cpl_act_establish *)skb->data;
	unsigned short tcp_opt = ntohs(req->tcp_opt);
	unsigned int tid = GET_TID(req);
	unsigned int atid = TID_TID_G(ntohl(req->tos_atid));
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct tid_info *t = lldi->tids;
	u32 rcv_isn = be32_to_cpu(req->rcv_isn);

	csk = lookup_atid(t, atid);
	if (unlikely(!csk)) {
		pr_err("NO conn. for atid %u, cdev 0x%p.\n", atid, cdev);
		goto rel_skb;
	}

	if (csk->atid != atid) {
		pr_err("bad conn atid %u, csk 0x%p,%u,0x%lx,tid %u, atid %u.\n",
			atid, csk, csk->state, csk->flags, csk->tid, csk->atid);
		goto rel_skb;
	}

	pr_info_ipaddr("atid 0x%x, tid 0x%x, csk 0x%p,%u,0x%lx, isn %u.\n",
		       (&csk->saddr), (&csk->daddr),
		       atid, tid, csk, csk->state, csk->flags, rcv_isn);

	module_put(cdev->owner);

	cxgbi_sock_get(csk);
	csk->tid = tid;
	cxgb4_insert_tid(lldi->tids, csk, tid, csk->csk_family);
	cxgbi_sock_set_flag(csk, CTPF_HAS_TID);

	free_atid(csk);

	spin_lock_bh(&csk->lock);
	if (unlikely(csk->state != CTP_ACTIVE_OPEN))
		pr_info("csk 0x%p,%u,0x%lx,%u, got EST.\n",
			csk, csk->state, csk->flags, csk->tid);

	if (csk->retry_timer.function) {
		del_timer(&csk->retry_timer);
		csk->retry_timer.function = NULL;
	}

	csk->copied_seq = csk->rcv_wup = csk->rcv_nxt = rcv_isn;
	/*
	 * Causes the first RX_DATA_ACK to supply any Rx credits we couldn't
	 * pass through opt0.
	 */
	if (csk->rcv_win > (RCV_BUFSIZ_MASK << 10))
		csk->rcv_wup -= csk->rcv_win - (RCV_BUFSIZ_MASK << 10);

	csk->advmss = lldi->mtus[TCPOPT_MSS_G(tcp_opt)] - 40;
	if (TCPOPT_TSTAMP_G(tcp_opt))
		csk->advmss -= 12;
	if (csk->advmss < 128)
		csk->advmss = 128;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p, mss_idx %u, advmss %u.\n",
			csk, TCPOPT_MSS_G(tcp_opt), csk->advmss);

	cxgbi_sock_established(csk, ntohl(req->snd_isn), ntohs(req->tcp_opt));

	if (unlikely(cxgbi_sock_flag(csk, CTPF_ACTIVE_CLOSE_NEEDED)))
		send_abort_req(csk);
	else {
		if (skb_queue_len(&csk->write_queue))
			push_tx_frames(csk, 0);
		cxgbi_conn_tx_open(csk);
	}
	spin_unlock_bh(&csk->lock);

rel_skb:
	__kfree_skb(skb);
}