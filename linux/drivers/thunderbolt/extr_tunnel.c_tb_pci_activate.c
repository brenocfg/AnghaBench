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
struct tb_tunnel {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; } ;

/* Variables and functions */
 int tb_pci_port_enable (int /*<<< orphan*/ ,int) ; 
 scalar_t__ tb_port_is_pcie_up (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb_pci_activate(struct tb_tunnel *tunnel, bool activate)
{
	int res;

	res = tb_pci_port_enable(tunnel->src_port, activate);
	if (res)
		return res;

	if (tb_port_is_pcie_up(tunnel->dst_port))
		return tb_pci_port_enable(tunnel->dst_port, activate);

	return 0;
}