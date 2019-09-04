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
struct tcp_sock {int nonagle; } ;
struct sock {int dummy; } ;
struct chtls_sock {scalar_t__ wr_credits; scalar_t__ wr_max_credits; struct chtls_dev* cdev; } ;
struct chtls_dev {int dummy; } ;

/* Variables and functions */
 int TCP_NAGLE_OFF ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static bool should_push(struct sock *sk)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct chtls_dev *cdev = csk->cdev;
	struct tcp_sock *tp = tcp_sk(sk);

	/*
	 * If we've released our offload resources there's nothing to do ...
	 */
	if (!cdev)
		return false;

	/*
	 * If there aren't any work requests in flight, or there isn't enough
	 * data in flight, or Nagle is off then send the current TX_DATA
	 * otherwise hold it and wait to accumulate more data.
	 */
	return csk->wr_credits == csk->wr_max_credits ||
		(tp->nonagle & TCP_NAGLE_OFF);
}