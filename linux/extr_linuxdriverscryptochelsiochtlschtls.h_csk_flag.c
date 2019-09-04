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
struct chtls_sock {int /*<<< orphan*/  flags; } ;
typedef  enum csk_flags { ____Placeholder_csk_flags } csk_flags ;

/* Variables and functions */
 int /*<<< orphan*/  csk_conn_inline (struct chtls_sock*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock const*) ; 
 int test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int csk_flag(const struct sock *sk, enum csk_flags flag)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	if (!csk_conn_inline(csk))
		return 0;
	return test_bit(flag, &csk->flags);
}