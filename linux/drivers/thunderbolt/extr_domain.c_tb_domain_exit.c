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
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_bus_type ; 
 int /*<<< orphan*/  tb_domain_ida ; 
 int /*<<< orphan*/  tb_switch_exit () ; 
 int /*<<< orphan*/  tb_xdomain_exit () ; 

void tb_domain_exit(void)
{
	bus_unregister(&tb_bus_type);
	ida_destroy(&tb_domain_ida);
	tb_switch_exit();
	tb_xdomain_exit();
}