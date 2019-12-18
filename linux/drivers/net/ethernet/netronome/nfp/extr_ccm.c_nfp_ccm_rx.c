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
struct sk_buff {int len; } ;
struct nfp_ccm_hdr {int dummy; } ;
struct nfp_ccm {int /*<<< orphan*/  wq; int /*<<< orphan*/  replies; int /*<<< orphan*/  tag_allocator; struct nfp_app* app; } ;
struct nfp_app {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  ccm_warn (struct nfp_app*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 unsigned int nfp_ccm_get_tag (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_ctrl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void nfp_ccm_rx(struct nfp_ccm *ccm, struct sk_buff *skb)
{
	struct nfp_app *app = ccm->app;
	unsigned int tag;

	if (unlikely(skb->len < sizeof(struct nfp_ccm_hdr))) {
		ccm_warn(app, "cmsg drop - too short %d!\n", skb->len);
		goto err_free;
	}

	nfp_ctrl_lock(app->ctrl);

	tag = nfp_ccm_get_tag(skb);
	if (unlikely(!test_bit(tag, ccm->tag_allocator))) {
		ccm_warn(app, "cmsg drop - no one is waiting for tag %u!\n",
			 tag);
		goto err_unlock;
	}

	__skb_queue_tail(&ccm->replies, skb);
	wake_up_interruptible_all(&ccm->wq);

	nfp_ctrl_unlock(app->ctrl);
	return;

err_unlock:
	nfp_ctrl_unlock(app->ctrl);
err_free:
	dev_kfree_skb_any(skb);
}