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
struct ipu_vdi {int /*<<< orphan*/  lock; int /*<<< orphan*/  use_count; int /*<<< orphan*/  module; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_module_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_vdi_enable(struct ipu_vdi *vdi)
{
	unsigned long flags;

	spin_lock_irqsave(&vdi->lock, flags);

	if (!vdi->use_count)
		ipu_module_enable(vdi->ipu, vdi->module);

	vdi->use_count++;

	spin_unlock_irqrestore(&vdi->lock, flags);

	return 0;
}