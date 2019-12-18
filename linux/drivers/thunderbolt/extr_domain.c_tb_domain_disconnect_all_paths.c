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
struct tb {int dummy; } ;

/* Variables and functions */
 int bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disconnect_xdomain ; 
 int /*<<< orphan*/  tb_bus_type ; 
 int tb_domain_disconnect_pcie_paths (struct tb*) ; 

int tb_domain_disconnect_all_paths(struct tb *tb)
{
	int ret;

	ret = tb_domain_disconnect_pcie_paths(tb);
	if (ret)
		return ret;

	return bus_for_each_dev(&tb_bus_type, NULL, tb, disconnect_xdomain);
}