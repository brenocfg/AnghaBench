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
struct chtls_sock {int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  chtls_push_frames (struct chtls_sock*,int) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void push_frames_if_head(struct sock *sk)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	if (skb_queue_len(&csk->txq) == 1)
		chtls_push_frames(csk, 1);
}