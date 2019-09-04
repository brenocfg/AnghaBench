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
struct chtls_sock {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_UPDATE_RCV_WND ; 
 unsigned int MAX_RCV_WND ; 
 unsigned int MIN_RCV_WND ; 
 int /*<<< orphan*/  csk_set_flag (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int tcp_full_space (struct sock*) ; 

__attribute__((used)) static unsigned int select_rcv_wnd(struct chtls_sock *csk)
{
	unsigned int rcvwnd;
	unsigned int wnd;
	struct sock *sk;

	sk = csk->sk;
	wnd = tcp_full_space(sk);

	if (wnd < MIN_RCV_WND)
		wnd = MIN_RCV_WND;

	rcvwnd = MAX_RCV_WND;

	csk_set_flag(csk, CSK_UPDATE_RCV_WND);
	return min(wnd, rcvwnd);
}