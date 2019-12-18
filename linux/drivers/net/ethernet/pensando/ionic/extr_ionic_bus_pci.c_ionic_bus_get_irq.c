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
struct ionic {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int pci_irq_vector (int /*<<< orphan*/ ,unsigned int) ; 

int ionic_bus_get_irq(struct ionic *ionic, unsigned int num)
{
	return pci_irq_vector(ionic->pdev, num);
}