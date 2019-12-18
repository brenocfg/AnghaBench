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
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct radeon_cs_packet {size_t idx; int opcode; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
#define  PACKET3_ALLOC_GDS 178 
#define  PACKET3_ATOMIC 177 
#define  PACKET3_ATOMIC_GDS 176 
#define  PACKET3_CLEAR_STATE 175 
#define  PACKET3_COND_EXEC 174 
#define  PACKET3_COND_WRITE 173 
#define  PACKET3_CONTEXT_CONTROL 172 
#define  PACKET3_COPY_DATA 171 
#define  PACKET3_COPY_DW 170 
#define  PACKET3_CP_DMA 169 
#define  PACKET3_DISPATCH_DIRECT 168 
#define  PACKET3_DISPATCH_INDIRECT 167 
#define  PACKET3_DRAW_INDEX_2 166 
#define  PACKET3_DRAW_INDEX_AUTO 165 
#define  PACKET3_DRAW_INDEX_IMMD 164 
#define  PACKET3_DRAW_INDEX_INDIRECT 163 
#define  PACKET3_DRAW_INDEX_INDIRECT_MULTI 162 
#define  PACKET3_DRAW_INDEX_MULTI_AUTO 161 
#define  PACKET3_DRAW_INDEX_MULTI_ELEMENT 160 
#define  PACKET3_DRAW_INDEX_OFFSET_2 159 
#define  PACKET3_DRAW_INDIRECT 158 
#define  PACKET3_DRAW_INDIRECT_MULTI 157 
#define  PACKET3_EVENT_WRITE 156 
#define  PACKET3_EVENT_WRITE_EOP 155 
#define  PACKET3_EVENT_WRITE_EOS 154 
#define  PACKET3_INCREMENT_DE_COUNTER 153 
#define  PACKET3_INDEX_BASE 152 
#define  PACKET3_INDEX_BUFFER_SIZE 151 
#define  PACKET3_INDEX_TYPE 150 
#define  PACKET3_MEM_WRITE 149 
#define  PACKET3_ME_WRITE 148 
#define  PACKET3_MPEG_INDEX 147 
#define  PACKET3_NOP 146 
#define  PACKET3_NUM_INSTANCES 145 
#define  PACKET3_OCCLUSION_QUERY 144 
#define  PACKET3_PFP_SYNC_ME 143 
#define  PACKET3_PRED_EXEC 142 
#define  PACKET3_SET_BASE 141 
#define  PACKET3_SET_CONFIG_REG 140 
 size_t PACKET3_SET_CONFIG_REG_END ; 
 size_t PACKET3_SET_CONFIG_REG_START ; 
#define  PACKET3_SET_CONTEXT_REG 139 
#define  PACKET3_SET_CONTEXT_REG_INDIRECT 138 
#define  PACKET3_SET_PREDICATION 137 
#define  PACKET3_SET_SH_REG 136 
#define  PACKET3_SET_SH_REG_OFFSET 135 
#define  PACKET3_STRMOUT_BUFFER_UPDATE 134 
#define  PACKET3_SURFACE_SYNC 133 
#define  PACKET3_WAIT_ON_AVAIL_BUFFER 132 
#define  PACKET3_WAIT_ON_CE_COUNTER 131 
#define  PACKET3_WAIT_REG_MEM 130 
#define  PACKET3_WRITE_DATA 129 
#define  PACKET3_WRITE_GDS_RAM 128 
 int si_vm_packet3_cp_dma_check (size_t*,size_t) ; 
 int /*<<< orphan*/  si_vm_reg_valid (size_t) ; 

__attribute__((used)) static int si_vm_packet3_gfx_check(struct radeon_device *rdev,
				   u32 *ib, struct radeon_cs_packet *pkt)
{
	int r;
	u32 idx = pkt->idx + 1;
	u32 idx_value = ib[idx];
	u32 start_reg, end_reg, reg, i;

	switch (pkt->opcode) {
	case PACKET3_NOP:
	case PACKET3_SET_BASE:
	case PACKET3_CLEAR_STATE:
	case PACKET3_INDEX_BUFFER_SIZE:
	case PACKET3_DISPATCH_DIRECT:
	case PACKET3_DISPATCH_INDIRECT:
	case PACKET3_ALLOC_GDS:
	case PACKET3_WRITE_GDS_RAM:
	case PACKET3_ATOMIC_GDS:
	case PACKET3_ATOMIC:
	case PACKET3_OCCLUSION_QUERY:
	case PACKET3_SET_PREDICATION:
	case PACKET3_COND_EXEC:
	case PACKET3_PRED_EXEC:
	case PACKET3_DRAW_INDIRECT:
	case PACKET3_DRAW_INDEX_INDIRECT:
	case PACKET3_INDEX_BASE:
	case PACKET3_DRAW_INDEX_2:
	case PACKET3_CONTEXT_CONTROL:
	case PACKET3_INDEX_TYPE:
	case PACKET3_DRAW_INDIRECT_MULTI:
	case PACKET3_DRAW_INDEX_AUTO:
	case PACKET3_DRAW_INDEX_IMMD:
	case PACKET3_NUM_INSTANCES:
	case PACKET3_DRAW_INDEX_MULTI_AUTO:
	case PACKET3_STRMOUT_BUFFER_UPDATE:
	case PACKET3_DRAW_INDEX_OFFSET_2:
	case PACKET3_DRAW_INDEX_MULTI_ELEMENT:
	case PACKET3_DRAW_INDEX_INDIRECT_MULTI:
	case PACKET3_MPEG_INDEX:
	case PACKET3_WAIT_REG_MEM:
	case PACKET3_MEM_WRITE:
	case PACKET3_PFP_SYNC_ME:
	case PACKET3_SURFACE_SYNC:
	case PACKET3_EVENT_WRITE:
	case PACKET3_EVENT_WRITE_EOP:
	case PACKET3_EVENT_WRITE_EOS:
	case PACKET3_SET_CONTEXT_REG:
	case PACKET3_SET_CONTEXT_REG_INDIRECT:
	case PACKET3_SET_SH_REG:
	case PACKET3_SET_SH_REG_OFFSET:
	case PACKET3_INCREMENT_DE_COUNTER:
	case PACKET3_WAIT_ON_CE_COUNTER:
	case PACKET3_WAIT_ON_AVAIL_BUFFER:
	case PACKET3_ME_WRITE:
		break;
	case PACKET3_COPY_DATA:
		if ((idx_value & 0xf00) == 0) {
			reg = ib[idx + 3] * 4;
			if (!si_vm_reg_valid(reg))
				return -EINVAL;
		}
		break;
	case PACKET3_WRITE_DATA:
		if ((idx_value & 0xf00) == 0) {
			start_reg = ib[idx + 1] * 4;
			if (idx_value & 0x10000) {
				if (!si_vm_reg_valid(start_reg))
					return -EINVAL;
			} else {
				for (i = 0; i < (pkt->count - 2); i++) {
					reg = start_reg + (4 * i);
					if (!si_vm_reg_valid(reg))
						return -EINVAL;
				}
			}
		}
		break;
	case PACKET3_COND_WRITE:
		if (idx_value & 0x100) {
			reg = ib[idx + 5] * 4;
			if (!si_vm_reg_valid(reg))
				return -EINVAL;
		}
		break;
	case PACKET3_COPY_DW:
		if (idx_value & 0x2) {
			reg = ib[idx + 3] * 4;
			if (!si_vm_reg_valid(reg))
				return -EINVAL;
		}
		break;
	case PACKET3_SET_CONFIG_REG:
		start_reg = (idx_value << 2) + PACKET3_SET_CONFIG_REG_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		if ((start_reg < PACKET3_SET_CONFIG_REG_START) ||
		    (start_reg >= PACKET3_SET_CONFIG_REG_END) ||
		    (end_reg >= PACKET3_SET_CONFIG_REG_END)) {
			DRM_ERROR("bad PACKET3_SET_CONFIG_REG\n");
			return -EINVAL;
		}
		for (i = 0; i < pkt->count; i++) {
			reg = start_reg + (4 * i);
			if (!si_vm_reg_valid(reg))
				return -EINVAL;
		}
		break;
	case PACKET3_CP_DMA:
		r = si_vm_packet3_cp_dma_check(ib, idx);
		if (r)
			return r;
		break;
	default:
		DRM_ERROR("Invalid GFX packet3: 0x%x\n", pkt->opcode);
		return -EINVAL;
	}
	return 0;
}