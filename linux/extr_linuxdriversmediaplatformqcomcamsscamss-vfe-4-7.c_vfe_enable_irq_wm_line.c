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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct vfe_device {int dummy; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_0_IRQ_MASK_0 ; 
 int VFE_0_IRQ_MASK_0_IMAGE_MASTER_n_PING_PONG (scalar_t__) ; 
 int VFE_0_IRQ_MASK_0_line_n_REG_UPDATE (int) ; 
 int /*<<< orphan*/  VFE_0_IRQ_MASK_1 ; 
 int VFE_0_IRQ_MASK_1_IMAGE_MASTER_n_BUS_OVERFLOW (scalar_t__) ; 
 int VFE_0_IRQ_MASK_1_RDIn_SOF (int) ; 
 int /*<<< orphan*/  vfe_reg_clr (struct vfe_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_reg_set (struct vfe_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vfe_enable_irq_wm_line(struct vfe_device *vfe, u8 wm,
				   enum vfe_line_id line_id, u8 enable)
{
	u32 irq_en0 = VFE_0_IRQ_MASK_0_IMAGE_MASTER_n_PING_PONG(wm) |
		      VFE_0_IRQ_MASK_0_line_n_REG_UPDATE(line_id);
	u32 irq_en1 = VFE_0_IRQ_MASK_1_IMAGE_MASTER_n_BUS_OVERFLOW(wm) |
		      VFE_0_IRQ_MASK_1_RDIn_SOF(line_id);

	if (enable) {
		vfe_reg_set(vfe, VFE_0_IRQ_MASK_0, irq_en0);
		vfe_reg_set(vfe, VFE_0_IRQ_MASK_1, irq_en1);
	} else {
		vfe_reg_clr(vfe, VFE_0_IRQ_MASK_0, irq_en0);
		vfe_reg_clr(vfe, VFE_0_IRQ_MASK_1, irq_en1);
	}
}