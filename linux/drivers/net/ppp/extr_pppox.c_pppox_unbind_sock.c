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
struct sock {int sk_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int PPPOX_BOUND ; 
 int PPPOX_CONNECTED ; 
 int PPPOX_DEAD ; 
 int /*<<< orphan*/  ppp_unregister_channel (int /*<<< orphan*/ *) ; 
 TYPE_1__* pppox_sk (struct sock*) ; 

void pppox_unbind_sock(struct sock *sk)
{
	/* Clear connection to ppp device, if attached. */

	if (sk->sk_state & (PPPOX_BOUND | PPPOX_CONNECTED)) {
		ppp_unregister_channel(&pppox_sk(sk)->chan);
		sk->sk_state = PPPOX_DEAD;
	}
}