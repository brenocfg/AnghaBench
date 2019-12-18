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
struct ican3_dev {int /*<<< orphan*/  echoq; } ;

/* Variables and functions */
 struct sk_buff* can_create_echo_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void ican3_put_echo_skb(struct ican3_dev *mod, struct sk_buff *skb)
{
	skb = can_create_echo_skb(skb);
	if (!skb)
		return;

	/* save this skb for tx interrupt echo handling */
	skb_queue_tail(&mod->echoq, skb);
}