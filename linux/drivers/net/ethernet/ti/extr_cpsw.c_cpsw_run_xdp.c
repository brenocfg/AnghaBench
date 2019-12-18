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
struct xdp_frame {int dummy; } ;
struct xdp_buff {int dummy; } ;
struct page {int dummy; } ;
struct net_device {int dummy; } ;
struct cpsw_priv {int /*<<< orphan*/  xdp_prog; struct net_device* ndev; struct cpsw_common* cpsw; } ;
struct cpsw_common {int /*<<< orphan*/ * page_pool; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int CPSW_XDP_CONSUMED ; 
 int CPSW_XDP_PASS ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 int /*<<< orphan*/  cpsw_xdp_tx_frame (struct cpsw_priv*,struct xdp_frame*,struct page*) ; 
 int /*<<< orphan*/  page_pool_recycle_direct (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  trace_xdp_exception (struct net_device*,struct bpf_prog*,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int /*<<< orphan*/  xdp_do_flush_map () ; 
 int /*<<< orphan*/  xdp_do_redirect (struct net_device*,struct xdp_buff*,struct bpf_prog*) ; 

__attribute__((used)) static int cpsw_run_xdp(struct cpsw_priv *priv, int ch, struct xdp_buff *xdp,
			struct page *page)
{
	struct cpsw_common *cpsw = priv->cpsw;
	struct net_device *ndev = priv->ndev;
	int ret = CPSW_XDP_CONSUMED;
	struct xdp_frame *xdpf;
	struct bpf_prog *prog;
	u32 act;

	rcu_read_lock();

	prog = READ_ONCE(priv->xdp_prog);
	if (!prog) {
		ret = CPSW_XDP_PASS;
		goto out;
	}

	act = bpf_prog_run_xdp(prog, xdp);
	switch (act) {
	case XDP_PASS:
		ret = CPSW_XDP_PASS;
		break;
	case XDP_TX:
		xdpf = convert_to_xdp_frame(xdp);
		if (unlikely(!xdpf))
			goto drop;

		cpsw_xdp_tx_frame(priv, xdpf, page);
		break;
	case XDP_REDIRECT:
		if (xdp_do_redirect(ndev, xdp, prog))
			goto drop;

		/*  Have to flush here, per packet, instead of doing it in bulk
		 *  at the end of the napi handler. The RX devices on this
		 *  particular hardware is sharing a common queue, so the
		 *  incoming device might change per packet.
		 */
		xdp_do_flush_map();
		break;
	default:
		bpf_warn_invalid_xdp_action(act);
		/* fall through */
	case XDP_ABORTED:
		trace_xdp_exception(ndev, prog, act);
		/* fall through -- handle aborts by dropping packet */
	case XDP_DROP:
		goto drop;
	}
out:
	rcu_read_unlock();
	return ret;
drop:
	rcu_read_unlock();
	page_pool_recycle_direct(cpsw->page_pool[ch], page);
	return ret;
}