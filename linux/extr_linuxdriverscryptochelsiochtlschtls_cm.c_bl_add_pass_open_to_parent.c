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
struct sock {int dummy; } ;
struct sk_buff {struct sock* sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 TYPE_1__* BLOG_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  add_pass_open_to_parent (struct sock*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void bl_add_pass_open_to_parent(struct sock *lsk, struct sk_buff *skb)
{
	struct sock *child = skb->sk;

	skb->sk = NULL;
	add_pass_open_to_parent(child, lsk, BLOG_SKB_CB(skb)->cdev);
	kfree_skb(skb);
}