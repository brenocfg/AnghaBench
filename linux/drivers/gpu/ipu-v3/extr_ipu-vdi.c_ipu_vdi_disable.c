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
struct ipu_vdi {int /*<<< orphan*/  lock; int /*<<< orphan*/  module; int /*<<< orphan*/  ipu; scalar_t__ use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_module_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_vdi_disable(struct ipu_vdi *vdi)
{
	unsigned long flags;

	spin_lock_irqsave(&vdi->lock, flags);

	if (vdi->use_count) {
		if (!--vdi->use_count)
			ipu_module_disable(vdi->ipu, vdi->module);
	}

	spin_unlock_irqrestore(&vdi->lock, flags);

	return 0;
}