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
struct nfp_ccm_mbox_cmsg_cb {int posted; } ;

/* Variables and functions */

__attribute__((used)) static void nfp_ccm_mbox_mark_posted(struct sk_buff *skb)
{
	struct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	cb->posted = true;
}