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
struct cxl_irq_ranges {int* offset; int* range; } ;
struct cxl {TYPE_1__* guest; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_alloc_lock; } ;

/* Variables and functions */
 int CXL_IRQ_RANGES ; 
 int ENOSPC ; 
 scalar_t__ irq_alloc_range (struct cxl*,int,int*) ; 
 int /*<<< orphan*/  irq_free_range (struct cxl*,int,int) ; 
 int /*<<< orphan*/  memset (struct cxl_irq_ranges*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int guest_alloc_irq_ranges(struct cxl_irq_ranges *irqs,
				struct cxl *adapter, unsigned int num)
{
	int i, try, irq;

	memset(irqs, 0, sizeof(struct cxl_irq_ranges));

	spin_lock(&adapter->guest->irq_alloc_lock);
	for (i = 0; i < CXL_IRQ_RANGES && num; i++) {
		try = num;
		while (try) {
			if (irq_alloc_range(adapter, try, &irq) == 0)
				break;
			try /= 2;
		}
		if (!try)
			goto error;
		irqs->offset[i] = irq;
		irqs->range[i] = try;
		num -= try;
	}
	if (num)
		goto error;
	spin_unlock(&adapter->guest->irq_alloc_lock);
	return 0;

error:
	for (i = 0; i < CXL_IRQ_RANGES; i++)
		irq_free_range(adapter, irqs->offset[i], irqs->range[i]);
	spin_unlock(&adapter->guest->irq_alloc_lock);
	return -ENOSPC;
}