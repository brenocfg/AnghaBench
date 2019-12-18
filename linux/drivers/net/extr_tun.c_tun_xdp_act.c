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
struct xdp_buff {int dummy; } ;
struct tun_struct {TYPE_1__* pcpu_stats; int /*<<< orphan*/  dev; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; } ;

/* Variables and functions */
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xdp_exception (int /*<<< orphan*/ ,struct bpf_prog*,int) ; 
 int tun_xdp_tx (int /*<<< orphan*/ ,struct xdp_buff*) ; 
 int xdp_do_redirect (int /*<<< orphan*/ ,struct xdp_buff*,struct bpf_prog*) ; 

__attribute__((used)) static int tun_xdp_act(struct tun_struct *tun, struct bpf_prog *xdp_prog,
		       struct xdp_buff *xdp, u32 act)
{
	int err;

	switch (act) {
	case XDP_REDIRECT:
		err = xdp_do_redirect(tun->dev, xdp, xdp_prog);
		if (err)
			return err;
		break;
	case XDP_TX:
		err = tun_xdp_tx(tun->dev, xdp);
		if (err < 0)
			return err;
		break;
	case XDP_PASS:
		break;
	default:
		bpf_warn_invalid_xdp_action(act);
		/* fall through */
	case XDP_ABORTED:
		trace_xdp_exception(tun->dev, xdp_prog, act);
		/* fall through */
	case XDP_DROP:
		this_cpu_inc(tun->pcpu_stats->rx_dropped);
		break;
	}

	return act;
}