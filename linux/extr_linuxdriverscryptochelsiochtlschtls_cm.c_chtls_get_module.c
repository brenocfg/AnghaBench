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
struct sock {int dummy; } ;
struct inet_connection_sock {TYPE_1__* icsk_ulp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chtls_get_module(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);

	if (!try_module_get(icsk->icsk_ulp_ops->owner))
		return -1;

	return 0;
}