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
struct sock {int /*<<< orphan*/ * sk_user_data; int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_state_change; } ;
struct siw_cep {int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_state_change; } ;

/* Variables and functions */

__attribute__((used)) static void siw_sk_restore_upcalls(struct sock *sk, struct siw_cep *cep)
{
	sk->sk_state_change = cep->sk_state_change;
	sk->sk_data_ready = cep->sk_data_ready;
	sk->sk_write_space = cep->sk_write_space;
	sk->sk_error_report = cep->sk_error_report;
	sk->sk_user_data = NULL;
}