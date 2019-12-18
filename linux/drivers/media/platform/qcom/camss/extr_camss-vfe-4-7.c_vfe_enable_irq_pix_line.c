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
typedef  int u8 ;
typedef  int u32 ;
struct vfe_output {unsigned int wm_num; int* wm_idx; } ;
struct vfe_device {TYPE_1__* line; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;
struct TYPE_2__ {struct vfe_output output; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_0_IRQ_COMPOSITE_MASK_0 ; 
 int /*<<< orphan*/  VFE_0_IRQ_MASK_0 ; 
 int VFE_0_IRQ_MASK_0_CAMIF_EOF ; 
 int VFE_0_IRQ_MASK_0_CAMIF_SOF ; 
 int VFE_0_IRQ_MASK_0_IMAGE_COMPOSITE_DONE_n (int) ; 
 int VFE_0_IRQ_MASK_0_line_n_REG_UPDATE (int) ; 
 int /*<<< orphan*/  VFE_0_IRQ_MASK_1 ; 
 int VFE_0_IRQ_MASK_1_CAMIF_ERROR ; 
 int VFE_0_IRQ_MASK_1_IMAGE_MASTER_n_BUS_OVERFLOW (int) ; 
 int /*<<< orphan*/  vfe_reg_clr (struct vfe_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_reg_set (struct vfe_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vfe_enable_irq_pix_line(struct vfe_device *vfe, u8 comp,
				    enum vfe_line_id line_id, u8 enable)
{
	struct vfe_output *output = &vfe->line[line_id].output;
	unsigned int i;
	u32 irq_en0;
	u32 irq_en1;
	u32 comp_mask = 0;

	irq_en0 = VFE_0_IRQ_MASK_0_CAMIF_SOF;
	irq_en0 |= VFE_0_IRQ_MASK_0_CAMIF_EOF;
	irq_en0 |= VFE_0_IRQ_MASK_0_IMAGE_COMPOSITE_DONE_n(comp);
	irq_en0 |= VFE_0_IRQ_MASK_0_line_n_REG_UPDATE(line_id);
	irq_en1 = VFE_0_IRQ_MASK_1_CAMIF_ERROR;
	for (i = 0; i < output->wm_num; i++) {
		irq_en1 |= VFE_0_IRQ_MASK_1_IMAGE_MASTER_n_BUS_OVERFLOW(
							output->wm_idx[i]);
		comp_mask |= (1 << output->wm_idx[i]) << comp * 8;
	}

	if (enable) {
		vfe_reg_set(vfe, VFE_0_IRQ_MASK_0, irq_en0);
		vfe_reg_set(vfe, VFE_0_IRQ_MASK_1, irq_en1);
		vfe_reg_set(vfe, VFE_0_IRQ_COMPOSITE_MASK_0, comp_mask);
	} else {
		vfe_reg_clr(vfe, VFE_0_IRQ_MASK_0, irq_en0);
		vfe_reg_clr(vfe, VFE_0_IRQ_MASK_1, irq_en1);
		vfe_reg_clr(vfe, VFE_0_IRQ_COMPOSITE_MASK_0, comp_mask);
	}
}