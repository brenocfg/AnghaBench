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
struct nfp_ccm_mbox_cmsg_cb {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_MBOX_CMSG_STATE_BUSY ; 

__attribute__((used)) static void nfp_ccm_mbox_set_busy(struct sk_buff *skb)
{
	struct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	cb->state = NFP_NET_MBOX_CMSG_STATE_BUSY;
}