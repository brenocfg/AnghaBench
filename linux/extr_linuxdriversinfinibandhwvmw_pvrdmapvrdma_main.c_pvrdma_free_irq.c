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
struct pvrdma_dev {int nr_vectors; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int) ; 

__attribute__((used)) static void pvrdma_free_irq(struct pvrdma_dev *dev)
{
	int i;

	dev_dbg(&dev->pdev->dev, "freeing interrupts\n");
	for (i = 0; i < dev->nr_vectors; i++)
		free_irq(pci_irq_vector(dev->pdev, i), dev);
}