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
struct device {int dummy; } ;
struct cio2_queue {int /*<<< orphan*/  fbpt; int /*<<< orphan*/  fbpt_bus_addr; } ;
struct cio2_device {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO2_FBPT_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cio2_fbpt_init(struct cio2_device *cio2, struct cio2_queue *q)
{
	struct device *dev = &cio2->pci_dev->dev;

	q->fbpt = dma_alloc_coherent(dev, CIO2_FBPT_SIZE, &q->fbpt_bus_addr,
				     GFP_KERNEL);
	if (!q->fbpt)
		return -ENOMEM;

	return 0;
}