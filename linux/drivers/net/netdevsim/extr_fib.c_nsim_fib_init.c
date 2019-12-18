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
 int /*<<< orphan*/  nsim_fib_dump_inconsistent ; 
 int /*<<< orphan*/  nsim_fib_nb ; 
 int /*<<< orphan*/  nsim_fib_net_ops ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int register_fib_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int register_pernet_subsys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_pernet_subsys (int /*<<< orphan*/ *) ; 

int nsim_fib_init(void)
{
	int err;

	err = register_pernet_subsys(&nsim_fib_net_ops);
	if (err < 0) {
		pr_err("Failed to register pernet subsystem\n");
		goto err_out;
	}

	err = register_fib_notifier(&nsim_fib_nb, nsim_fib_dump_inconsistent);
	if (err < 0) {
		pr_err("Failed to register fib notifier\n");
		unregister_pernet_subsys(&nsim_fib_net_ops);
		goto err_out;
	}

err_out:
	return err;
}