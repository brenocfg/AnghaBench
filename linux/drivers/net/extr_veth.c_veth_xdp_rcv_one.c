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
typedef  int u32 ;
struct xdp_frame {int data; int headroom; int len; int metasize; int /*<<< orphan*/  mem; } ;
struct xdp_buff {int data; int data_end; int data_meta; TYPE_1__* rxq; void* data_hard_start; } ;
struct veth_xdp_tx_bq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem; } ;
struct veth_rq {int /*<<< orphan*/  dev; TYPE_1__ xdp_rxq; int /*<<< orphan*/  xdp_prog; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 unsigned int VETH_XDP_REDIR ; 
 unsigned int VETH_XDP_TX ; 
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct bpf_prog*) ; 
 struct bpf_prog* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  trace_xdp_exception (int /*<<< orphan*/ ,struct bpf_prog*,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 struct sk_buff* veth_build_skb (void*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  veth_xdp_tx (int /*<<< orphan*/ ,struct xdp_buff*,struct veth_xdp_tx_bq*) ; 
 int /*<<< orphan*/  xdp_do_redirect (int /*<<< orphan*/ ,struct xdp_buff*,struct bpf_prog*) ; 
 int /*<<< orphan*/  xdp_release_frame (struct xdp_frame*) ; 
 int /*<<< orphan*/  xdp_return_frame (struct xdp_frame*) ; 
 int /*<<< orphan*/  xdp_scrub_frame (struct xdp_frame*) ; 

__attribute__((used)) static struct sk_buff *veth_xdp_rcv_one(struct veth_rq *rq,
					struct xdp_frame *frame,
					unsigned int *xdp_xmit,
					struct veth_xdp_tx_bq *bq)
{
	void *hard_start = frame->data - frame->headroom;
	void *head = hard_start - sizeof(struct xdp_frame);
	int len = frame->len, delta = 0;
	struct xdp_frame orig_frame;
	struct bpf_prog *xdp_prog;
	unsigned int headroom;
	struct sk_buff *skb;

	rcu_read_lock();
	xdp_prog = rcu_dereference(rq->xdp_prog);
	if (likely(xdp_prog)) {
		struct xdp_buff xdp;
		u32 act;

		xdp.data_hard_start = hard_start;
		xdp.data = frame->data;
		xdp.data_end = frame->data + frame->len;
		xdp.data_meta = frame->data - frame->metasize;
		xdp.rxq = &rq->xdp_rxq;

		act = bpf_prog_run_xdp(xdp_prog, &xdp);

		switch (act) {
		case XDP_PASS:
			delta = frame->data - xdp.data;
			len = xdp.data_end - xdp.data;
			break;
		case XDP_TX:
			orig_frame = *frame;
			xdp.data_hard_start = head;
			xdp.rxq->mem = frame->mem;
			if (unlikely(veth_xdp_tx(rq->dev, &xdp, bq) < 0)) {
				trace_xdp_exception(rq->dev, xdp_prog, act);
				frame = &orig_frame;
				goto err_xdp;
			}
			*xdp_xmit |= VETH_XDP_TX;
			rcu_read_unlock();
			goto xdp_xmit;
		case XDP_REDIRECT:
			orig_frame = *frame;
			xdp.data_hard_start = head;
			xdp.rxq->mem = frame->mem;
			if (xdp_do_redirect(rq->dev, &xdp, xdp_prog)) {
				frame = &orig_frame;
				goto err_xdp;
			}
			*xdp_xmit |= VETH_XDP_REDIR;
			rcu_read_unlock();
			goto xdp_xmit;
		default:
			bpf_warn_invalid_xdp_action(act);
			/* fall through */
		case XDP_ABORTED:
			trace_xdp_exception(rq->dev, xdp_prog, act);
			/* fall through */
		case XDP_DROP:
			goto err_xdp;
		}
	}
	rcu_read_unlock();

	headroom = sizeof(struct xdp_frame) + frame->headroom - delta;
	skb = veth_build_skb(head, headroom, len, 0);
	if (!skb) {
		xdp_return_frame(frame);
		goto err;
	}

	xdp_release_frame(frame);
	xdp_scrub_frame(frame);
	skb->protocol = eth_type_trans(skb, rq->dev);
err:
	return skb;
err_xdp:
	rcu_read_unlock();
	xdp_return_frame(frame);
xdp_xmit:
	return NULL;
}