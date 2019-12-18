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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct nfp_net {TYPE_1__ mbox_cmsg; } ;

/* Variables and functions */
 int skb_queue_is_first (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static bool nfp_ccm_mbox_is_first(struct nfp_net *nn, struct sk_buff *skb)
{
	return skb_queue_is_first(&nn->mbox_cmsg.queue, skb);
}