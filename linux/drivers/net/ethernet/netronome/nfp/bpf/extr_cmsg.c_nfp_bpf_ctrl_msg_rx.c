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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct nfp_app_bpf {int /*<<< orphan*/  ccm; } ;
struct nfp_app {struct nfp_app_bpf* priv; } ;
struct cmsg_reply_map_simple {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFP_CCM_TYPE_BPF_BPF_EVENT ; 
 int /*<<< orphan*/  cmsg_warn (struct nfp_app_bpf*,char*,int) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_bpf_event_output (struct nfp_app_bpf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfp_ccm_get_type (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_ccm_rx (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void nfp_bpf_ctrl_msg_rx(struct nfp_app *app, struct sk_buff *skb)
{
	struct nfp_app_bpf *bpf = app->priv;

	if (unlikely(skb->len < sizeof(struct cmsg_reply_map_simple))) {
		cmsg_warn(bpf, "cmsg drop - too short %d!\n", skb->len);
		dev_kfree_skb_any(skb);
		return;
	}

	if (nfp_ccm_get_type(skb) == NFP_CCM_TYPE_BPF_BPF_EVENT) {
		if (!nfp_bpf_event_output(bpf, skb->data, skb->len))
			dev_consume_skb_any(skb);
		else
			dev_kfree_skb_any(skb);
	}

	nfp_ccm_rx(&bpf->ccm, skb);
}