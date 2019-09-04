#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {void* len; void* cmd_more; } ;
struct TYPE_8__ {void* lock_addr; void* dlen; void* len16; void* cmd; } ;
struct TYPE_7__ {int reneg_to_write_rx; int /*<<< orphan*/  mfs; scalar_t__ protocol; void* flowid_len16; void* op_to_compl; } ;
struct tls_key_req {TYPE_4__ sc_imm; TYPE_3__ req; TYPE_2__ wr; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_10__ {int rxkey; int txkey; scalar_t__ tx_seq_no; int /*<<< orphan*/  txqid; } ;
struct chtls_sock {int tid; int wr_credits; int wr_unacked; TYPE_5__ tlshws; int /*<<< orphan*/  egress_dev; int /*<<< orphan*/  txq; struct sock* sk; struct chtls_dev* cdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
struct chtls_dev {TYPE_1__ kmap; } ;
struct _key_ctx {int dummy; } ;

/* Variables and functions */
 int AEAD_H_SIZE ; 
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int DIV_ROUND_UP (int,int) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FW_ULPTX_WR ; 
 int FW_WR_ATOMIC_V (unsigned int) ; 
 int FW_WR_COMPL_F ; 
 int FW_WR_FLOWID_V (int) ; 
 int FW_WR_LEN16_V (int) ; 
 int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int T5_ULP_MEMIO_IMM_V (int) ; 
 int T5_ULP_MEMIO_ORDER_V (int) ; 
 int TCB_ULP_RAW_M ; 
 int /*<<< orphan*/  TCB_ULP_RAW_V (int) ; 
 int TF_TLS_ACTIVE_V (int) ; 
 int TF_TLS_CONTROL_V (int) ; 
 int TF_TLS_ENABLE_V (int) ; 
 int TF_TLS_KEY_SIZE_V (int) ; 
 int /*<<< orphan*/  TLS_MFS ; 
 int TLS_RX ; 
 int TLS_TX ; 
 int ULPTX_CMD_V (int /*<<< orphan*/ ) ; 
 int ULP_MEMIO_ADDR_V (int) ; 
 int ULP_MEMIO_DATA_LEN_V (int) ; 
 int /*<<< orphan*/  ULP_TX_MEM_WRITE ; 
 int /*<<< orphan*/  ULP_TX_SC_IMM ; 
 scalar_t__ __skb_put_zero (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int chtls_key_info (struct chtls_sock*,struct _key_ctx*,int,int) ; 
 int /*<<< orphan*/  chtls_push_frames (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chtls_set_scmd (struct chtls_sock*) ; 
 int chtls_set_tcb_field (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int chtls_set_tcb_keyid (struct sock*,int) ; 
 int chtls_set_tcb_quiesce (struct sock*,int /*<<< orphan*/ ) ; 
 int chtls_set_tcb_seqno (struct sock*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  enqueue_wr (struct chtls_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  free_tls_keyid (struct sock*) ; 
 int get_new_keyid (struct chtls_sock*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int keyid_to_addr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

int chtls_setkey(struct chtls_sock *csk, u32 keylen, u32 optname)
{
	struct tls_key_req *kwr;
	struct chtls_dev *cdev;
	struct _key_ctx *kctx;
	int wrlen, klen, len;
	struct sk_buff *skb;
	struct sock *sk;
	int keyid;
	int kaddr;
	int ret;

	cdev = csk->cdev;
	sk = csk->sk;

	klen = roundup((keylen + AEAD_H_SIZE) + sizeof(*kctx), 32);
	wrlen = roundup(sizeof(*kwr), 16);
	len = klen + wrlen;

	/* Flush out-standing data before new key takes effect */
	if (optname == TLS_TX) {
		lock_sock(sk);
		if (skb_queue_len(&csk->txq))
			chtls_push_frames(csk, 0);
		release_sock(sk);
	}

	skb = alloc_skb(len, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	keyid = get_new_keyid(csk, optname);
	if (keyid < 0) {
		ret = -ENOSPC;
		goto out_nokey;
	}

	kaddr = keyid_to_addr(cdev->kmap.start, keyid);
	kwr = (struct tls_key_req *)__skb_put_zero(skb, len);
	kwr->wr.op_to_compl =
		cpu_to_be32(FW_WR_OP_V(FW_ULPTX_WR) | FW_WR_COMPL_F |
		      FW_WR_ATOMIC_V(1U));
	kwr->wr.flowid_len16 =
		cpu_to_be32(FW_WR_LEN16_V(DIV_ROUND_UP(len, 16) |
			    FW_WR_FLOWID_V(csk->tid)));
	kwr->wr.protocol = 0;
	kwr->wr.mfs = htons(TLS_MFS);
	kwr->wr.reneg_to_write_rx = optname;

	/* ulptx command */
	kwr->req.cmd = cpu_to_be32(ULPTX_CMD_V(ULP_TX_MEM_WRITE) |
			    T5_ULP_MEMIO_ORDER_V(1) |
			    T5_ULP_MEMIO_IMM_V(1));
	kwr->req.len16 = cpu_to_be32((csk->tid << 8) |
			      DIV_ROUND_UP(len - sizeof(kwr->wr), 16));
	kwr->req.dlen = cpu_to_be32(ULP_MEMIO_DATA_LEN_V(klen >> 5));
	kwr->req.lock_addr = cpu_to_be32(ULP_MEMIO_ADDR_V(kaddr));

	/* sub command */
	kwr->sc_imm.cmd_more = cpu_to_be32(ULPTX_CMD_V(ULP_TX_SC_IMM));
	kwr->sc_imm.len = cpu_to_be32(klen);

	/* key info */
	kctx = (struct _key_ctx *)(kwr + 1);
	ret = chtls_key_info(csk, kctx, keylen, optname);
	if (ret)
		goto out_notcb;

	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->tlshws.txqid);
	csk->wr_credits -= DIV_ROUND_UP(len, 16);
	csk->wr_unacked += DIV_ROUND_UP(len, 16);
	enqueue_wr(csk, skb);
	cxgb4_ofld_send(csk->egress_dev, skb);

	chtls_set_scmd(csk);
	/* Clear quiesce for Rx key */
	if (optname == TLS_RX) {
		ret = chtls_set_tcb_keyid(sk, keyid);
		if (ret)
			goto out_notcb;
		ret = chtls_set_tcb_field(sk, 0,
					  TCB_ULP_RAW_V(TCB_ULP_RAW_M),
					  TCB_ULP_RAW_V((TF_TLS_KEY_SIZE_V(1) |
					  TF_TLS_CONTROL_V(1) |
					  TF_TLS_ACTIVE_V(1) |
					  TF_TLS_ENABLE_V(1))));
		if (ret)
			goto out_notcb;
		ret = chtls_set_tcb_seqno(sk);
		if (ret)
			goto out_notcb;
		ret = chtls_set_tcb_quiesce(sk, 0);
		if (ret)
			goto out_notcb;
		csk->tlshws.rxkey = keyid;
	} else {
		csk->tlshws.tx_seq_no = 0;
		csk->tlshws.txkey = keyid;
	}

	return ret;
out_notcb:
	free_tls_keyid(sk);
out_nokey:
	kfree_skb(skb);
	return ret;
}