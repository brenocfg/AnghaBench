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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nfp_app_bpf {TYPE_1__* app; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 struct sk_buff* __nfp_bpf_reply (struct nfp_app_bpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *nfp_bpf_reply(struct nfp_app_bpf *bpf, u16 tag)
{
	struct sk_buff *skb;

	nfp_ctrl_lock(bpf->app->ctrl);
	skb = __nfp_bpf_reply(bpf, tag);
	nfp_ctrl_unlock(bpf->app->ctrl);

	return skb;
}