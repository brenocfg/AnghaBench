#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {TYPE_1__* faults; } ;
struct TYPE_6__ {TYPE_2__ ih; } ;
struct amdgpu_device {TYPE_3__ irq; } ;
struct TYPE_4__ {scalar_t__ count; int /*<<< orphan*/  lock; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int chash_table_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void amdgpu_ih_clear_fault(struct amdgpu_device *adev, u64 key)
{
	unsigned long flags;
	int r;

	if (!adev->irq.ih.faults)
		return;

	spin_lock_irqsave(&adev->irq.ih.faults->lock, flags);

	r = chash_table_remove(&adev->irq.ih.faults->hash, key, NULL);
	if (!WARN_ON_ONCE(r < 0)) {
		adev->irq.ih.faults->count--;
		WARN_ON_ONCE(adev->irq.ih.faults->count < 0);
	}

	spin_unlock_irqrestore(&adev->irq.ih.faults->lock, flags);
}