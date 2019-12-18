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
struct ipu_vdi {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDI_C ; 
 int /*<<< orphan*/  VDI_FSIZE ; 
 int /*<<< orphan*/  ipu_vdi_write (struct ipu_vdi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_vdi_unsetup(struct ipu_vdi *vdi)
{
	unsigned long flags;

	spin_lock_irqsave(&vdi->lock, flags);
	ipu_vdi_write(vdi, 0, VDI_FSIZE);
	ipu_vdi_write(vdi, 0, VDI_C);
	spin_unlock_irqrestore(&vdi->lock, flags);
}