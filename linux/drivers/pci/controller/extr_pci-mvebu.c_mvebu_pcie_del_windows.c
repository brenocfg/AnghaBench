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
struct mvebu_pcie_port {int dummy; } ;
typedef  size_t phys_addr_t ;

/* Variables and functions */
 int fls (size_t) ; 
 int /*<<< orphan*/  mvebu_mbus_del_window (size_t,size_t) ; 

__attribute__((used)) static void mvebu_pcie_del_windows(struct mvebu_pcie_port *port,
				   phys_addr_t base, size_t size)
{
	while (size) {
		size_t sz = 1 << (fls(size) - 1);

		mvebu_mbus_del_window(base, sz);
		base += sz;
		size -= sz;
	}
}