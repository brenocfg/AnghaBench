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
struct nfp_ccm_mbox_cmsg_cb {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_MBOX_CMSG_STATE_DONE ; 

__attribute__((used)) static bool nfp_ccm_mbox_done(struct sk_buff *skb)
{
	struct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	return cb->state == NFP_NET_MBOX_CMSG_STATE_DONE;
}