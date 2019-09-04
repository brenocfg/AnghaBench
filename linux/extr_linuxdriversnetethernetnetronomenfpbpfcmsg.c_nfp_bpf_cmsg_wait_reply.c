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
struct sk_buff {int dummy; } ;
struct nfp_app_bpf {int /*<<< orphan*/  cmsg_wq; } ;
typedef  enum nfp_bpf_cmsg_type { ____Placeholder_nfp_bpf_cmsg_type } nfp_bpf_cmsg_type ;

/* Variables and functions */
 int ERESTARTSYS ; 
 struct sk_buff* ERR_PTR (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cmsg_warn (struct nfp_app_bpf*,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct sk_buff* nfp_bpf_reply (struct nfp_app_bpf*,int) ; 
 struct sk_buff* nfp_bpf_reply_drop_tag (struct nfp_app_bpf*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
nfp_bpf_cmsg_wait_reply(struct nfp_app_bpf *bpf, enum nfp_bpf_cmsg_type type,
			int tag)
{
	struct sk_buff *skb;
	int i, err;

	for (i = 0; i < 50; i++) {
		udelay(4);
		skb = nfp_bpf_reply(bpf, tag);
		if (skb)
			return skb;
	}

	err = wait_event_interruptible_timeout(bpf->cmsg_wq,
					       skb = nfp_bpf_reply(bpf, tag),
					       msecs_to_jiffies(5000));
	/* We didn't get a response - try last time and atomically drop
	 * the tag even if no response is matched.
	 */
	if (!skb)
		skb = nfp_bpf_reply_drop_tag(bpf, tag);
	if (err < 0) {
		cmsg_warn(bpf, "%s waiting for response to 0x%02x: %d\n",
			  err == ERESTARTSYS ? "interrupted" : "error",
			  type, err);
		return ERR_PTR(err);
	}
	if (!skb) {
		cmsg_warn(bpf, "timeout waiting for response to 0x%02x\n",
			  type);
		return ERR_PTR(-ETIMEDOUT);
	}

	return skb;
}