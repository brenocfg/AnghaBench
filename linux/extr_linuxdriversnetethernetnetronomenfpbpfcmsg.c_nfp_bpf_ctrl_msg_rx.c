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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct nfp_app_bpf {TYPE_1__* app; int /*<<< orphan*/  cmsg_wq; int /*<<< orphan*/  cmsg_replies; int /*<<< orphan*/  tag_allocator; } ;
struct nfp_app {struct nfp_app_bpf* priv; } ;
struct cmsg_reply_map_simple {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 scalar_t__ CMSG_TYPE_BPF_EVENT ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  cmsg_warn (struct nfp_app_bpf*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 unsigned int nfp_bpf_cmsg_get_tag (struct sk_buff*) ; 
 scalar_t__ nfp_bpf_cmsg_get_type (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_bpf_event_output (struct nfp_app_bpf*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nfp_ctrl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void nfp_bpf_ctrl_msg_rx(struct nfp_app *app, struct sk_buff *skb)
{
	struct nfp_app_bpf *bpf = app->priv;
	unsigned int tag;

	if (unlikely(skb->len < sizeof(struct cmsg_reply_map_simple))) {
		cmsg_warn(bpf, "cmsg drop - too short %d!\n", skb->len);
		goto err_free;
	}

	if (nfp_bpf_cmsg_get_type(skb) == CMSG_TYPE_BPF_EVENT) {
		if (!nfp_bpf_event_output(bpf, skb->data, skb->len))
			dev_consume_skb_any(skb);
		else
			dev_kfree_skb_any(skb);
		return;
	}

	nfp_ctrl_lock(bpf->app->ctrl);

	tag = nfp_bpf_cmsg_get_tag(skb);
	if (unlikely(!test_bit(tag, bpf->tag_allocator))) {
		cmsg_warn(bpf, "cmsg drop - no one is waiting for tag %u!\n",
			  tag);
		goto err_unlock;
	}

	__skb_queue_tail(&bpf->cmsg_replies, skb);
	wake_up_interruptible_all(&bpf->cmsg_wq);

	nfp_ctrl_unlock(bpf->app->ctrl);

	return;
err_unlock:
	nfp_ctrl_unlock(bpf->app->ctrl);
err_free:
	dev_kfree_skb_any(skb);
}