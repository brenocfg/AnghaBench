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
struct cxl {TYPE_1__* guest; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_alloc_lock; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ irq_alloc_range (struct cxl*,int,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int guest_alloc_one_irq(struct cxl *adapter)
{
	int irq;

	spin_lock(&adapter->guest->irq_alloc_lock);
	if (irq_alloc_range(adapter, 1, &irq))
		irq = -ENOSPC;
	spin_unlock(&adapter->guest->irq_alloc_lock);
	return irq;
}