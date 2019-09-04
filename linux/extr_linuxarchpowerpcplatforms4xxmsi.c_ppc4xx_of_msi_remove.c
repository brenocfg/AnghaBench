#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bitmap; } ;
struct ppc4xx_msi {int* msi_virqs; int /*<<< orphan*/  msi_dev; int /*<<< orphan*/  msi_regs; TYPE_2__ bitmap; } ;
struct TYPE_3__ {struct ppc4xx_msi* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  msi_bitmap_free (TYPE_2__*) ; 
 int msi_irqs ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppc4xx_of_msi_remove(struct platform_device *dev)
{
	struct ppc4xx_msi *msi = dev->dev.platform_data;
	int i;
	int virq;

	for (i = 0; i < msi_irqs; i++) {
		virq = msi->msi_virqs[i];
		if (virq)
			irq_dispose_mapping(virq);
	}

	if (msi->bitmap.bitmap)
		msi_bitmap_free(&msi->bitmap);
	iounmap(msi->msi_regs);
	of_node_put(msi->msi_dev);

	return 0;
}