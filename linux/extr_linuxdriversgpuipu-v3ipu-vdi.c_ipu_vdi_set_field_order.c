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
typedef  int v4l2_std_id ;
typedef  int u32 ;
struct ipu_vdi {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  V4L2_FIELD_BOTTOM 133 
#define  V4L2_FIELD_INTERLACED_BT 132 
#define  V4L2_FIELD_INTERLACED_TB 131 
#define  V4L2_FIELD_SEQ_BT 130 
#define  V4L2_FIELD_SEQ_TB 129 
#define  V4L2_FIELD_TOP 128 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  VDI_C ; 
 int VDI_C_TOP_FIELD_AUTO_1 ; 
 int VDI_C_TOP_FIELD_MAN_1 ; 
 int ipu_vdi_read (struct ipu_vdi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_vdi_write (struct ipu_vdi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_vdi_set_field_order(struct ipu_vdi *vdi, v4l2_std_id std, u32 field)
{
	bool top_field_0 = false;
	unsigned long flags;
	u32 reg;

	switch (field) {
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_SEQ_TB:
	case V4L2_FIELD_TOP:
		top_field_0 = true;
		break;
	case V4L2_FIELD_INTERLACED_BT:
	case V4L2_FIELD_SEQ_BT:
	case V4L2_FIELD_BOTTOM:
		top_field_0 = false;
		break;
	default:
		top_field_0 = (std & V4L2_STD_525_60) ? true : false;
		break;
	}

	spin_lock_irqsave(&vdi->lock, flags);

	reg = ipu_vdi_read(vdi, VDI_C);
	if (top_field_0)
		reg &= ~(VDI_C_TOP_FIELD_MAN_1 | VDI_C_TOP_FIELD_AUTO_1);
	else
		reg |= VDI_C_TOP_FIELD_MAN_1 | VDI_C_TOP_FIELD_AUTO_1;
	ipu_vdi_write(vdi, reg, VDI_C);

	spin_unlock_irqrestore(&vdi->lock, flags);
}