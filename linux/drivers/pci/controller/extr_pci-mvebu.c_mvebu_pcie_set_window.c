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
struct mvebu_pcie_window {scalar_t__ base; scalar_t__ remap; scalar_t__ size; } ;
struct mvebu_pcie_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvebu_pcie_add_windows (struct mvebu_pcie_port*,unsigned int,unsigned int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mvebu_pcie_del_windows (struct mvebu_pcie_port*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mvebu_pcie_set_window(struct mvebu_pcie_port *port,
				  unsigned int target, unsigned int attribute,
				  const struct mvebu_pcie_window *desired,
				  struct mvebu_pcie_window *cur)
{
	if (desired->base == cur->base && desired->remap == cur->remap &&
	    desired->size == cur->size)
		return;

	if (cur->size != 0) {
		mvebu_pcie_del_windows(port, cur->base, cur->size);
		cur->size = 0;
		cur->base = 0;

		/*
		 * If something tries to change the window while it is enabled
		 * the change will not be done atomically. That would be
		 * difficult to do in the general case.
		 */
	}

	if (desired->size == 0)
		return;

	mvebu_pcie_add_windows(port, target, attribute, desired->base,
			       desired->size, desired->remap);
	*cur = *desired;
}