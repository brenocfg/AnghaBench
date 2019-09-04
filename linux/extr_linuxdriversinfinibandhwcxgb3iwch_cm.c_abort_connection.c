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
struct iwch_ep {int /*<<< orphan*/  com; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORTING ; 
 int /*<<< orphan*/  pr_debug (char*,char*,struct iwch_ep*) ; 
 int /*<<< orphan*/  send_abort (struct iwch_ep*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void abort_connection(struct iwch_ep *ep, struct sk_buff *skb, gfp_t gfp)
{
	pr_debug("%s ep %p\n", __FILE__, ep);
	state_set(&ep->com, ABORTING);
	send_abort(ep, skb, gfp);
}