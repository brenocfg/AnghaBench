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
struct sk_buff {scalar_t__ cb; } ;
struct nfp_ccm_mbox_cmsg_cb {int max_len; unsigned int exp_reply; int posted; scalar_t__ err; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_MBOX_CMSG_STATE_QUEUED ; 

__attribute__((used)) static void
nfp_ccm_mbox_msg_init(struct sk_buff *skb, unsigned int exp_reply, int max_len)
{
	struct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	cb->state = NFP_NET_MBOX_CMSG_STATE_QUEUED;
	cb->err = 0;
	cb->max_len = max_len;
	cb->exp_reply = exp_reply;
	cb->posted = false;
}