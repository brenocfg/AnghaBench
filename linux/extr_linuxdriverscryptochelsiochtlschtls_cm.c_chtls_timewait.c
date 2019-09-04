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
struct TYPE_2__ {int /*<<< orphan*/  ts_recent_stamp; } ;
struct tcp_sock {scalar_t__ srtt_us; TYPE_1__ rx_opt; int /*<<< orphan*/  rcv_nxt; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_TIME_WAIT ; 
 int /*<<< orphan*/  ktime_get_seconds () ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_wait (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chtls_timewait(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	tp->rcv_nxt++;
	tp->rx_opt.ts_recent_stamp = ktime_get_seconds();
	tp->srtt_us = 0;
	tcp_time_wait(sk, TCP_TIME_WAIT, 0);
}