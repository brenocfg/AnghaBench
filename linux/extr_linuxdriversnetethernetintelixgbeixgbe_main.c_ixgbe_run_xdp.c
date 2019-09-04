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
struct xdp_buff {int /*<<< orphan*/  data_hard_start; } ;
struct sk_buff {int dummy; } ;
struct ixgbe_ring {int /*<<< orphan*/  netdev; int /*<<< orphan*/  xdp_prog; } ;
struct ixgbe_adapter {int /*<<< orphan*/  netdev; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 struct sk_buff* ERR_PTR (int) ; 
 int IXGBE_XDP_CONSUMED ; 
 int IXGBE_XDP_PASS ; 
 int IXGBE_XDP_REDIR ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 int ixgbe_xmit_xdp_ring (struct ixgbe_adapter*,struct xdp_frame*) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  trace_xdp_exception (int /*<<< orphan*/ ,struct bpf_prog*,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int xdp_do_redirect (int /*<<< orphan*/ ,struct xdp_buff*,struct bpf_prog*) ; 

__attribute__((used)) static struct sk_buff *ixgbe_run_xdp(struct ixgbe_adapter *adapter,
				     struct ixgbe_ring *rx_ring,
				     struct xdp_buff *xdp)
{
	int err, result = IXGBE_XDP_PASS;
	struct bpf_prog *xdp_prog;
	struct xdp_frame *xdpf;
	u32 act;

	rcu_read_lock();
	xdp_prog = READ_ONCE(rx_ring->xdp_prog);

	if (!xdp_prog)
		goto xdp_out;

	prefetchw(xdp->data_hard_start); /* xdp_frame write */

	act = bpf_prog_run_xdp(xdp_prog, xdp);
	switch (act) {
	case XDP_PASS:
		break;
	case XDP_TX:
		xdpf = convert_to_xdp_frame(xdp);
		if (unlikely(!xdpf)) {
			result = IXGBE_XDP_CONSUMED;
			break;
		}
		result = ixgbe_xmit_xdp_ring(adapter, xdpf);
		break;
	case XDP_REDIRECT:
		err = xdp_do_redirect(adapter->netdev, xdp, xdp_prog);
		if (!err)
			result = IXGBE_XDP_REDIR;
		else
			result = IXGBE_XDP_CONSUMED;
		break;
	default:
		bpf_warn_invalid_xdp_action(act);
		/* fallthrough */
	case XDP_ABORTED:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, act);
		/* fallthrough -- handle aborts by dropping packet */
	case XDP_DROP:
		result = IXGBE_XDP_CONSUMED;
		break;
	}
xdp_out:
	rcu_read_unlock();
	return ERR_PTR(-result);
}