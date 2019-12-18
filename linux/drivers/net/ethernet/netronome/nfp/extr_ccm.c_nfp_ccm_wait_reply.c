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
struct nfp_ccm {int /*<<< orphan*/  wq; } ;
struct nfp_app {int dummy; } ;
typedef  enum nfp_ccm_type { ____Placeholder_nfp_ccm_type } nfp_ccm_type ;

/* Variables and functions */
 int ERESTARTSYS ; 
 struct sk_buff* ERR_PTR (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ccm_warn (struct nfp_app*,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct sk_buff* nfp_ccm_reply (struct nfp_ccm*,struct nfp_app*,int) ; 
 struct sk_buff* nfp_ccm_reply_drop_tag (struct nfp_ccm*,struct nfp_app*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
nfp_ccm_wait_reply(struct nfp_ccm *ccm, struct nfp_app *app,
		   enum nfp_ccm_type type, int tag)
{
	struct sk_buff *skb;
	int i, err;

	for (i = 0; i < 50; i++) {
		udelay(4);
		skb = nfp_ccm_reply(ccm, app, tag);
		if (skb)
			return skb;
	}

	err = wait_event_interruptible_timeout(ccm->wq,
					       skb = nfp_ccm_reply(ccm, app,
								   tag),
					       msecs_to_jiffies(5000));
	/* We didn't get a response - try last time and atomically drop
	 * the tag even if no response is matched.
	 */
	if (!skb)
		skb = nfp_ccm_reply_drop_tag(ccm, app, tag);
	if (err < 0) {
		ccm_warn(app, "%s waiting for response to 0x%02x: %d\n",
			 err == ERESTARTSYS ? "interrupted" : "error",
			 type, err);
		return ERR_PTR(err);
	}
	if (!skb) {
		ccm_warn(app, "timeout waiting for response to 0x%02x\n", type);
		return ERR_PTR(-ETIMEDOUT);
	}

	return skb;
}