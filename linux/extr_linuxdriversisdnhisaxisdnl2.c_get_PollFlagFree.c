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
struct PStack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  get_PollFlag (struct PStack*,struct sk_buff*) ; 

__attribute__((used)) static inline u_char
get_PollFlagFree(struct PStack *st, struct sk_buff *skb)
{
	u_char PF;

	PF = get_PollFlag(st, skb);
	dev_kfree_skb(skb);
	return (PF);
}