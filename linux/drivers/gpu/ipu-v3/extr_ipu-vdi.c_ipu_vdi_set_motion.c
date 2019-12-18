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
typedef  int /*<<< orphan*/  u32 ;
struct ipu_vdi {int /*<<< orphan*/  lock; } ;
typedef  enum ipu_motion_sel { ____Placeholder_ipu_motion_sel } ipu_motion_sel ;

/* Variables and functions */
#define  HIGH_MOTION 129 
#define  MED_MOTION 128 
 int /*<<< orphan*/  VDI_C ; 
 int /*<<< orphan*/  VDI_C_MOT_SEL_FULL ; 
 int /*<<< orphan*/  VDI_C_MOT_SEL_LOW ; 
 int /*<<< orphan*/  VDI_C_MOT_SEL_MASK ; 
 int /*<<< orphan*/  VDI_C_MOT_SEL_MED ; 
 int /*<<< orphan*/  ipu_vdi_read (struct ipu_vdi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_vdi_write (struct ipu_vdi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_vdi_set_motion(struct ipu_vdi *vdi, enum ipu_motion_sel motion_sel)
{
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(&vdi->lock, flags);

	reg = ipu_vdi_read(vdi, VDI_C);

	reg &= ~VDI_C_MOT_SEL_MASK;

	switch (motion_sel) {
	case MED_MOTION:
		reg |= VDI_C_MOT_SEL_MED;
		break;
	case HIGH_MOTION:
		reg |= VDI_C_MOT_SEL_FULL;
		break;
	default:
		reg |= VDI_C_MOT_SEL_LOW;
		break;
	}

	ipu_vdi_write(vdi, reg, VDI_C);

	spin_unlock_irqrestore(&vdi->lock, flags);
}