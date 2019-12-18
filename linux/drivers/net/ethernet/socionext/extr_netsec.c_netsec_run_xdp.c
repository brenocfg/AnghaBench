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
struct xdp_buff {int dummy; } ;
struct netsec_priv {int /*<<< orphan*/  ndev; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int NETSEC_XDP_CONSUMED ; 
 int NETSEC_XDP_PASS ; 
 int NETSEC_XDP_REDIR ; 
 int NETSEC_XDP_TX ; 
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 int netsec_xdp_xmit_back (struct netsec_priv*,struct xdp_buff*) ; 
 int /*<<< orphan*/  trace_xdp_exception (int /*<<< orphan*/ ,struct bpf_prog*,int) ; 
 int xdp_do_redirect (int /*<<< orphan*/ ,struct xdp_buff*,struct bpf_prog*) ; 
 int /*<<< orphan*/  xdp_return_buff (struct xdp_buff*) ; 

__attribute__((used)) static u32 netsec_run_xdp(struct netsec_priv *priv, struct bpf_prog *prog,
			  struct xdp_buff *xdp)
{
	u32 ret = NETSEC_XDP_PASS;
	int err;
	u32 act;

	act = bpf_prog_run_xdp(prog, xdp);

	switch (act) {
	case XDP_PASS:
		ret = NETSEC_XDP_PASS;
		break;
	case XDP_TX:
		ret = netsec_xdp_xmit_back(priv, xdp);
		if (ret != NETSEC_XDP_TX)
			xdp_return_buff(xdp);
		break;
	case XDP_REDIRECT:
		err = xdp_do_redirect(priv->ndev, xdp, prog);
		if (!err) {
			ret = NETSEC_XDP_REDIR;
		} else {
			ret = NETSEC_XDP_CONSUMED;
			xdp_return_buff(xdp);
		}
		break;
	default:
		bpf_warn_invalid_xdp_action(act);
		/* fall through */
	case XDP_ABORTED:
		trace_xdp_exception(priv->ndev, prog, act);
		/* fall through -- handle aborts by dropping packet */
	case XDP_DROP:
		ret = NETSEC_XDP_CONSUMED;
		xdp_return_buff(xdp);
		break;
	}

	return ret;
}