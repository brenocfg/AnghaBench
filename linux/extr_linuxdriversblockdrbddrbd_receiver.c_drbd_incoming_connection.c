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
struct sock {scalar_t__ sk_state; struct accept_wait_data* sk_user_data; } ;
struct accept_wait_data {void (* original_sk_state_change ) (struct sock*) ;int /*<<< orphan*/  door_bell; } ;

/* Variables and functions */
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_incoming_connection(struct sock *sk)
{
	struct accept_wait_data *ad = sk->sk_user_data;
	void (*state_change)(struct sock *sk);

	state_change = ad->original_sk_state_change;
	if (sk->sk_state == TCP_ESTABLISHED)
		complete(&ad->door_bell);
	state_change(sk);
}