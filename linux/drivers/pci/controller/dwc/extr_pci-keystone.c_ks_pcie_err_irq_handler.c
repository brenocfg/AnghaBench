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
struct keystone_pcie {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ks_pcie_handle_error_irq (struct keystone_pcie*) ; 

__attribute__((used)) static irqreturn_t ks_pcie_err_irq_handler(int irq, void *priv)
{
	struct keystone_pcie *ks_pcie = priv;

	return ks_pcie_handle_error_irq(ks_pcie);
}