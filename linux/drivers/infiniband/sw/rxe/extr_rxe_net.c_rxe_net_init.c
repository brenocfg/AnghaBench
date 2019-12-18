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
struct TYPE_2__ {int /*<<< orphan*/ * sk6; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ recv_sockets ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxe_net_exit () ; 
 int rxe_net_ipv4_init () ; 
 int rxe_net_ipv6_init () ; 
 int /*<<< orphan*/  rxe_net_notifier ; 

int rxe_net_init(void)
{
	int err;

	recv_sockets.sk6 = NULL;

	err = rxe_net_ipv4_init();
	if (err)
		return err;
	err = rxe_net_ipv6_init();
	if (err)
		goto err_out;
	err = register_netdevice_notifier(&rxe_net_notifier);
	if (err) {
		pr_err("Failed to register netdev notifier\n");
		goto err_out;
	}
	return 0;
err_out:
	rxe_net_exit();
	return err;
}