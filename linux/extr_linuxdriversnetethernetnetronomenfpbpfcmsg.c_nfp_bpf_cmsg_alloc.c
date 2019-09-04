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
struct nfp_app_bpf {int /*<<< orphan*/  app; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* nfp_app_ctrl_msg_alloc (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static struct sk_buff *
nfp_bpf_cmsg_alloc(struct nfp_app_bpf *bpf, unsigned int size)
{
	struct sk_buff *skb;

	skb = nfp_app_ctrl_msg_alloc(bpf->app, size, GFP_KERNEL);
	skb_put(skb, size);

	return skb;
}