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
struct ddb {int msi; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddb_irq_disable (struct ddb*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ddb*) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ddb_irq_exit(struct ddb *dev)
{
	ddb_irq_disable(dev);
	if (dev->msi == 2)
		free_irq(pci_irq_vector(dev->pdev, 1), dev);
	free_irq(pci_irq_vector(dev->pdev, 0), dev);
}