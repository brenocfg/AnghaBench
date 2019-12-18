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
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_state_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  siw_cm_llp_data_ready ; 
 int /*<<< orphan*/  siw_cm_llp_error_report ; 
 int /*<<< orphan*/  siw_cm_llp_state_change ; 
 int /*<<< orphan*/  siw_cm_llp_write_space ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void siw_sk_assign_cm_upcalls(struct sock *sk)
{
	write_lock_bh(&sk->sk_callback_lock);
	sk->sk_state_change = siw_cm_llp_state_change;
	sk->sk_data_ready = siw_cm_llp_data_ready;
	sk->sk_write_space = siw_cm_llp_write_space;
	sk->sk_error_report = siw_cm_llp_error_report;
	write_unlock_bh(&sk->sk_callback_lock);
}