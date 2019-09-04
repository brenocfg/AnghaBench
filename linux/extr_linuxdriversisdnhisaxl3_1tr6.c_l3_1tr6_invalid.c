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
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int dummy; } ;
struct l3_process {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l3_1tr6_release_req (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l3_1tr6_invalid(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;

	dev_kfree_skb(skb);
	l3_1tr6_release_req(pc, 0, NULL);
}