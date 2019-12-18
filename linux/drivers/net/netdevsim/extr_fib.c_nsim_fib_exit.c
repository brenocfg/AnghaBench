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

/* Variables and functions */
 int /*<<< orphan*/  nsim_fib_nb ; 
 int /*<<< orphan*/  nsim_fib_net_ops ; 
 int /*<<< orphan*/  unregister_fib_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_pernet_subsys (int /*<<< orphan*/ *) ; 

void nsim_fib_exit(void)
{
	unregister_fib_notifier(&nsim_fib_nb);
	unregister_pernet_subsys(&nsim_fib_net_ops);
}