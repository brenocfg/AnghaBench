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
 int /*<<< orphan*/  chtls_pass_open_arp_failure ; 
 int /*<<< orphan*/  process_cpl_msg (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void chtls_accept_rpl_arp_failure(void *handle,
					 struct sk_buff *skb)
{
	struct sock *sk = (struct sock *)handle;

	sock_hold(sk);
	process_cpl_msg(chtls_pass_open_arp_failure, sk, skb);
	sock_put(sk);
}