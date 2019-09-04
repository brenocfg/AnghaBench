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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_ABORT_SHUTDOWN ; 
 int /*<<< orphan*/  chtls_abort_conn (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  csk_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void handle_excess_rx(struct sock *sk, struct sk_buff *skb)
{
	if (!csk_flag(sk, CSK_ABORT_SHUTDOWN))
		chtls_abort_conn(sk, skb);

	kfree_skb(skb);
}