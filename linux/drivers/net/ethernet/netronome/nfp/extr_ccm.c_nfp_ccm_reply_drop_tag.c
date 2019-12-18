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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nfp_ccm {int dummy; } ;
struct nfp_app {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 struct sk_buff* __nfp_ccm_reply (struct nfp_ccm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ccm_free_tag (struct nfp_ccm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
nfp_ccm_reply_drop_tag(struct nfp_ccm *ccm, struct nfp_app *app, u16 tag)
{
	struct sk_buff *skb;

	nfp_ctrl_lock(app->ctrl);
	skb = __nfp_ccm_reply(ccm, tag);
	if (!skb)
		nfp_ccm_free_tag(ccm, tag);
	nfp_ctrl_unlock(app->ctrl);

	return skb;
}