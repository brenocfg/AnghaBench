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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int PACKET3_CP_DMA_CMD_DAIC ; 
 int PACKET3_CP_DMA_CMD_DAS ; 
 int PACKET3_CP_DMA_CMD_SAIC ; 
 int PACKET3_CP_DMA_CMD_SAS ; 
 int /*<<< orphan*/  si_vm_reg_valid (int) ; 

__attribute__((used)) static int si_vm_packet3_cp_dma_check(u32 *ib, u32 idx)
{
	u32 start_reg, reg, i;
	u32 command = ib[idx + 4];
	u32 info = ib[idx + 1];
	u32 idx_value = ib[idx];
	if (command & PACKET3_CP_DMA_CMD_SAS) {
		/* src address space is register */
		if (((info & 0x60000000) >> 29) == 0) {
			start_reg = idx_value << 2;
			if (command & PACKET3_CP_DMA_CMD_SAIC) {
				reg = start_reg;
				if (!si_vm_reg_valid(reg)) {
					DRM_ERROR("CP DMA Bad SRC register\n");
					return -EINVAL;
				}
			} else {
				for (i = 0; i < (command & 0x1fffff); i++) {
					reg = start_reg + (4 * i);
					if (!si_vm_reg_valid(reg)) {
						DRM_ERROR("CP DMA Bad SRC register\n");
						return -EINVAL;
					}
				}
			}
		}
	}
	if (command & PACKET3_CP_DMA_CMD_DAS) {
		/* dst address space is register */
		if (((info & 0x00300000) >> 20) == 0) {
			start_reg = ib[idx + 2];
			if (command & PACKET3_CP_DMA_CMD_DAIC) {
				reg = start_reg;
				if (!si_vm_reg_valid(reg)) {
					DRM_ERROR("CP DMA Bad DST register\n");
					return -EINVAL;
				}
			} else {
				for (i = 0; i < (command & 0x1fffff); i++) {
					reg = start_reg + (4 * i);
				if (!si_vm_reg_valid(reg)) {
						DRM_ERROR("CP DMA Bad DST register\n");
						return -EINVAL;
					}
				}
			}
		}
	}
	return 0;
}