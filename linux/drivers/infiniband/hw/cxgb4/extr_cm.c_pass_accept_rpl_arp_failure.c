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
struct c4iw_ep {int /*<<< orphan*/  com; int /*<<< orphan*/  hwtid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEAD ; 
 int /*<<< orphan*/  FAKE_CPL_PASS_PUT_EP_SAFE ; 
 int /*<<< orphan*/  __state_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_arp_failure_cpl (struct c4iw_ep*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pass_accept_rpl_arp_failure(void *handle, struct sk_buff *skb)
{
	struct c4iw_ep *ep = handle;

	pr_err("ARP failure during accept - tid %u - dropping connection\n",
	       ep->hwtid);

	__state_set(&ep->com, DEAD);
	queue_arp_failure_cpl(ep, skb, FAKE_CPL_PASS_PUT_EP_SAFE);
}