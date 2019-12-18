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
struct msi_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_dispose_mapping (unsigned int) ; 
 int /*<<< orphan*/  xilinx_pcie_destroy_msi (unsigned int) ; 

__attribute__((used)) static void xilinx_msi_teardown_irq(struct msi_controller *chip,
				    unsigned int irq)
{
	xilinx_pcie_destroy_msi(irq);
	irq_dispose_mapping(irq);
}