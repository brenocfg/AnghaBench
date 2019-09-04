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
struct radeon_ib {size_t length_dw; size_t* ptr; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
#define  DMA_PACKET_CONSTANT_FILL 131 
#define  DMA_PACKET_COPY 130 
#define  DMA_PACKET_NOP 129 
#define  DMA_PACKET_WRITE 128 
 int /*<<< orphan*/  DRM_ERROR (char*,size_t,size_t) ; 
 int EINVAL ; 
 size_t GET_DMA_CMD (size_t) ; 
 size_t GET_DMA_COUNT (size_t) ; 
 size_t GET_DMA_SUB_CMD (size_t) ; 

int evergreen_dma_ib_parse(struct radeon_device *rdev, struct radeon_ib *ib)
{
	u32 idx = 0;
	u32 header, cmd, count, sub_cmd;

	do {
		header = ib->ptr[idx];
		cmd = GET_DMA_CMD(header);
		count = GET_DMA_COUNT(header);
		sub_cmd = GET_DMA_SUB_CMD(header);

		switch (cmd) {
		case DMA_PACKET_WRITE:
			switch (sub_cmd) {
			/* tiled */
			case 8:
				idx += count + 7;
				break;
			/* linear */
			case 0:
				idx += count + 3;
				break;
			default:
				DRM_ERROR("bad DMA_PACKET_WRITE [%6d] 0x%08x sub cmd is not 0 or 8\n", idx, ib->ptr[idx]);
				return -EINVAL;
			}
			break;
		case DMA_PACKET_COPY:
			switch (sub_cmd) {
			/* Copy L2L, DW aligned */
			case 0x00:
				idx += 5;
				break;
			/* Copy L2T/T2L */
			case 0x08:
				idx += 9;
				break;
			/* Copy L2L, byte aligned */
			case 0x40:
				idx += 5;
				break;
			/* Copy L2L, partial */
			case 0x41:
				idx += 9;
				break;
			/* Copy L2L, DW aligned, broadcast */
			case 0x44:
				idx += 7;
				break;
			/* Copy L2T Frame to Field */
			case 0x48:
				idx += 10;
				break;
			/* Copy L2T/T2L, partial */
			case 0x49:
				idx += 12;
				break;
			/* Copy L2T broadcast */
			case 0x4b:
				idx += 10;
				break;
			/* Copy L2T/T2L (tile units) */
			case 0x4c:
				idx += 9;
				break;
			/* Copy T2T, partial (tile units) */
			case 0x4d:
				idx += 13;
				break;
			/* Copy L2T broadcast (tile units) */
			case 0x4f:
				idx += 10;
				break;
			default:
				DRM_ERROR("bad DMA_PACKET_COPY [%6d] 0x%08x invalid sub cmd\n", idx, ib->ptr[idx]);
				return -EINVAL;
			}
			break;
		case DMA_PACKET_CONSTANT_FILL:
			idx += 4;
			break;
		case DMA_PACKET_NOP:
			idx += 1;
			break;
		default:
			DRM_ERROR("Unknown packet type %d at %d !\n", cmd, idx);
			return -EINVAL;
		}
	} while (idx < ib->length_dw);

	return 0;
}