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
typedef  int uint32_t ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int* ptr; } ;
struct radeon_cs_parser {scalar_t__ idx; int /*<<< orphan*/  dev; int /*<<< orphan*/  family; struct radeon_cs_chunk* chunk_ib; TYPE_1__ ib; } ;
struct radeon_cs_chunk {scalar_t__ length_dw; } ;
struct radeon_bo_list {int gpu_offset; int /*<<< orphan*/  robj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_CAYMAN ; 
#define  DMA_PACKET_CONSTANT_FILL 131 
#define  DMA_PACKET_COPY 130 
#define  DMA_PACKET_NOP 129 
#define  DMA_PACKET_WRITE 128 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int GET_DMA_CMD (int) ; 
 int GET_DMA_COUNT (int) ; 
 int GET_DMA_SUB_CMD (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int r600_dma_cs_next_reloc (struct radeon_cs_parser*,struct radeon_bo_list**) ; 
 int radeon_bo_size (int /*<<< orphan*/ ) ; 
 int radeon_get_ib_value (struct radeon_cs_parser*,int) ; 
 int upper_32_bits (int) ; 

int evergreen_dma_cs_parse(struct radeon_cs_parser *p)
{
	struct radeon_cs_chunk *ib_chunk = p->chunk_ib;
	struct radeon_bo_list *src_reloc, *dst_reloc, *dst2_reloc;
	u32 header, cmd, count, sub_cmd;
	uint32_t *ib = p->ib.ptr;
	u32 idx;
	u64 src_offset, dst_offset, dst2_offset;
	int r;

	do {
		if (p->idx >= ib_chunk->length_dw) {
			DRM_ERROR("Can not parse packet at %d after CS end %d !\n",
				  p->idx, ib_chunk->length_dw);
			return -EINVAL;
		}
		idx = p->idx;
		header = radeon_get_ib_value(p, idx);
		cmd = GET_DMA_CMD(header);
		count = GET_DMA_COUNT(header);
		sub_cmd = GET_DMA_SUB_CMD(header);

		switch (cmd) {
		case DMA_PACKET_WRITE:
			r = r600_dma_cs_next_reloc(p, &dst_reloc);
			if (r) {
				DRM_ERROR("bad DMA_PACKET_WRITE\n");
				return -EINVAL;
			}
			switch (sub_cmd) {
			/* tiled */
			case 8:
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;

				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				p->idx += count + 7;
				break;
			/* linear */
			case 0:
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+2) & 0xff)) << 32;

				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
				ib[idx+2] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				p->idx += count + 3;
				break;
			default:
				DRM_ERROR("bad DMA_PACKET_WRITE [%6d] 0x%08x sub cmd is not 0 or 8\n", idx, header);
				return -EINVAL;
			}
			if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
				dev_warn(p->dev, "DMA write buffer too small (%llu %lu)\n",
					 dst_offset, radeon_bo_size(dst_reloc->robj));
				return -EINVAL;
			}
			break;
		case DMA_PACKET_COPY:
			r = r600_dma_cs_next_reloc(p, &src_reloc);
			if (r) {
				DRM_ERROR("bad DMA_PACKET_COPY\n");
				return -EINVAL;
			}
			r = r600_dma_cs_next_reloc(p, &dst_reloc);
			if (r) {
				DRM_ERROR("bad DMA_PACKET_COPY\n");
				return -EINVAL;
			}
			switch (sub_cmd) {
			/* Copy L2L, DW aligned */
			case 0x00:
				/* L2L, dw */
				src_offset = radeon_get_ib_value(p, idx+2);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0xff)) << 32;
				if ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) {
					dev_warn(p->dev, "DMA L2L, dw src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					return -EINVAL;
				}
				if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
					dev_warn(p->dev, "DMA L2L, dw dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					return -EINVAL;
				}
				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
				ib[idx+2] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+3] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				ib[idx+4] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 5;
				break;
			/* Copy L2T/T2L */
			case 0x08:
				/* detile bit */
				if (radeon_get_ib_value(p, idx + 2) & (1 << 31)) {
					/* tiled src, linear dst */
					src_offset = radeon_get_ib_value(p, idx+1);
					src_offset <<= 8;
					ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);

					dst_offset = radeon_get_ib_value(p, idx + 7);
					dst_offset |= ((u64)(radeon_get_ib_value(p, idx+8) & 0xff)) << 32;
					ib[idx+7] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				} else {
					/* linear src, tiled dst */
					src_offset = radeon_get_ib_value(p, idx+7);
					src_offset |= ((u64)(radeon_get_ib_value(p, idx+8) & 0xff)) << 32;
					ib[idx+7] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(src_reloc->gpu_offset) & 0xff;

					dst_offset = radeon_get_ib_value(p, idx+1);
					dst_offset <<= 8;
					ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				}
				if ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					return -EINVAL;
				}
				if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					return -EINVAL;
				}
				p->idx += 9;
				break;
			/* Copy L2L, byte aligned */
			case 0x40:
				/* L2L, byte */
				src_offset = radeon_get_ib_value(p, idx+2);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0xff)) << 32;
				if ((src_offset + count) > radeon_bo_size(src_reloc->robj)) {
					dev_warn(p->dev, "DMA L2L, byte src buffer too small (%llu %lu)\n",
							src_offset + count, radeon_bo_size(src_reloc->robj));
					return -EINVAL;
				}
				if ((dst_offset + count) > radeon_bo_size(dst_reloc->robj)) {
					dev_warn(p->dev, "DMA L2L, byte dst buffer too small (%llu %lu)\n",
							dst_offset + count, radeon_bo_size(dst_reloc->robj));
					return -EINVAL;
				}
				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xffffffff);
				ib[idx+2] += (u32)(src_reloc->gpu_offset & 0xffffffff);
				ib[idx+3] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				ib[idx+4] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 5;
				break;
			/* Copy L2L, partial */
			case 0x41:
				/* L2L, partial */
				if (p->family < CHIP_CAYMAN) {
					DRM_ERROR("L2L Partial is cayman only !\n");
					return -EINVAL;
				}
				ib[idx+1] += (u32)(src_reloc->gpu_offset & 0xffffffff);
				ib[idx+2] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				ib[idx+4] += (u32)(dst_reloc->gpu_offset & 0xffffffff);
				ib[idx+5] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;

				p->idx += 9;
				break;
			/* Copy L2L, DW aligned, broadcast */
			case 0x44:
				/* L2L, dw, broadcast */
				r = r600_dma_cs_next_reloc(p, &dst2_reloc);
				if (r) {
					DRM_ERROR("bad L2L, dw, broadcast DMA_PACKET_COPY\n");
					return -EINVAL;
				}
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset |= ((u64)(radeon_get_ib_value(p, idx+4) & 0xff)) << 32;
				dst2_offset = radeon_get_ib_value(p, idx+2);
				dst2_offset |= ((u64)(radeon_get_ib_value(p, idx+5) & 0xff)) << 32;
				src_offset = radeon_get_ib_value(p, idx+3);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+6) & 0xff)) << 32;
				if ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) {
					dev_warn(p->dev, "DMA L2L, dw, broadcast src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					return -EINVAL;
				}
				if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
					dev_warn(p->dev, "DMA L2L, dw, broadcast dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					return -EINVAL;
				}
				if ((dst2_offset + (count * 4)) > radeon_bo_size(dst2_reloc->robj)) {
					dev_warn(p->dev, "DMA L2L, dw, broadcast dst2 buffer too small (%llu %lu)\n",
							dst2_offset + (count * 4), radeon_bo_size(dst2_reloc->robj));
					return -EINVAL;
				}
				ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
				ib[idx+2] += (u32)(dst2_reloc->gpu_offset & 0xfffffffc);
				ib[idx+3] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+4] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				ib[idx+5] += upper_32_bits(dst2_reloc->gpu_offset) & 0xff;
				ib[idx+6] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 7;
				break;
			/* Copy L2T Frame to Field */
			case 0x48:
				if (radeon_get_ib_value(p, idx + 2) & (1 << 31)) {
					DRM_ERROR("bad L2T, frame to fields DMA_PACKET_COPY\n");
					return -EINVAL;
				}
				r = r600_dma_cs_next_reloc(p, &dst2_reloc);
				if (r) {
					DRM_ERROR("bad L2T, frame to fields DMA_PACKET_COPY\n");
					return -EINVAL;
				}
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;
				dst2_offset = radeon_get_ib_value(p, idx+2);
				dst2_offset <<= 8;
				src_offset = radeon_get_ib_value(p, idx+8);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+9) & 0xff)) << 32;
				if ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, frame to fields src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					return -EINVAL;
				}
				if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, frame to fields buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					return -EINVAL;
				}
				if ((dst2_offset + (count * 4)) > radeon_bo_size(dst2_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, frame to fields buffer too small (%llu %lu)\n",
							dst2_offset + (count * 4), radeon_bo_size(dst2_reloc->robj));
					return -EINVAL;
				}
				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				ib[idx+2] += (u32)(dst2_reloc->gpu_offset >> 8);
				ib[idx+8] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+9] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 10;
				break;
			/* Copy L2T/T2L, partial */
			case 0x49:
				/* L2T, T2L partial */
				if (p->family < CHIP_CAYMAN) {
					DRM_ERROR("L2T, T2L Partial is cayman only !\n");
					return -EINVAL;
				}
				/* detile bit */
				if (radeon_get_ib_value(p, idx + 2) & (1 << 31)) {
					/* tiled src, linear dst */
					ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);

					ib[idx+7] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				} else {
					/* linear src, tiled dst */
					ib[idx+7] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(src_reloc->gpu_offset) & 0xff;

					ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				}
				p->idx += 12;
				break;
			/* Copy L2T broadcast */
			case 0x4b:
				/* L2T, broadcast */
				if (radeon_get_ib_value(p, idx + 2) & (1 << 31)) {
					DRM_ERROR("bad L2T, broadcast DMA_PACKET_COPY\n");
					return -EINVAL;
				}
				r = r600_dma_cs_next_reloc(p, &dst2_reloc);
				if (r) {
					DRM_ERROR("bad L2T, broadcast DMA_PACKET_COPY\n");
					return -EINVAL;
				}
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;
				dst2_offset = radeon_get_ib_value(p, idx+2);
				dst2_offset <<= 8;
				src_offset = radeon_get_ib_value(p, idx+8);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+9) & 0xff)) << 32;
				if ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, broadcast src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					return -EINVAL;
				}
				if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, broadcast dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					return -EINVAL;
				}
				if ((dst2_offset + (count * 4)) > radeon_bo_size(dst2_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, broadcast dst2 buffer too small (%llu %lu)\n",
							dst2_offset + (count * 4), radeon_bo_size(dst2_reloc->robj));
					return -EINVAL;
				}
				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				ib[idx+2] += (u32)(dst2_reloc->gpu_offset >> 8);
				ib[idx+8] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+9] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 10;
				break;
			/* Copy L2T/T2L (tile units) */
			case 0x4c:
				/* L2T, T2L */
				/* detile bit */
				if (radeon_get_ib_value(p, idx + 2) & (1 << 31)) {
					/* tiled src, linear dst */
					src_offset = radeon_get_ib_value(p, idx+1);
					src_offset <<= 8;
					ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);

					dst_offset = radeon_get_ib_value(p, idx+7);
					dst_offset |= ((u64)(radeon_get_ib_value(p, idx+8) & 0xff)) << 32;
					ib[idx+7] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(dst_reloc->gpu_offset) & 0xff;
				} else {
					/* linear src, tiled dst */
					src_offset = radeon_get_ib_value(p, idx+7);
					src_offset |= ((u64)(radeon_get_ib_value(p, idx+8) & 0xff)) << 32;
					ib[idx+7] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
					ib[idx+8] += upper_32_bits(src_reloc->gpu_offset) & 0xff;

					dst_offset = radeon_get_ib_value(p, idx+1);
					dst_offset <<= 8;
					ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				}
				if ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, T2L src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					return -EINVAL;
				}
				if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, T2L dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					return -EINVAL;
				}
				p->idx += 9;
				break;
			/* Copy T2T, partial (tile units) */
			case 0x4d:
				/* T2T partial */
				if (p->family < CHIP_CAYMAN) {
					DRM_ERROR("L2T, T2L Partial is cayman only !\n");
					return -EINVAL;
				}
				ib[idx+1] += (u32)(src_reloc->gpu_offset >> 8);
				ib[idx+4] += (u32)(dst_reloc->gpu_offset >> 8);
				p->idx += 13;
				break;
			/* Copy L2T broadcast (tile units) */
			case 0x4f:
				/* L2T, broadcast */
				if (radeon_get_ib_value(p, idx + 2) & (1 << 31)) {
					DRM_ERROR("bad L2T, broadcast DMA_PACKET_COPY\n");
					return -EINVAL;
				}
				r = r600_dma_cs_next_reloc(p, &dst2_reloc);
				if (r) {
					DRM_ERROR("bad L2T, broadcast DMA_PACKET_COPY\n");
					return -EINVAL;
				}
				dst_offset = radeon_get_ib_value(p, idx+1);
				dst_offset <<= 8;
				dst2_offset = radeon_get_ib_value(p, idx+2);
				dst2_offset <<= 8;
				src_offset = radeon_get_ib_value(p, idx+8);
				src_offset |= ((u64)(radeon_get_ib_value(p, idx+9) & 0xff)) << 32;
				if ((src_offset + (count * 4)) > radeon_bo_size(src_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, broadcast src buffer too small (%llu %lu)\n",
							src_offset + (count * 4), radeon_bo_size(src_reloc->robj));
					return -EINVAL;
				}
				if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, broadcast dst buffer too small (%llu %lu)\n",
							dst_offset + (count * 4), radeon_bo_size(dst_reloc->robj));
					return -EINVAL;
				}
				if ((dst2_offset + (count * 4)) > radeon_bo_size(dst2_reloc->robj)) {
					dev_warn(p->dev, "DMA L2T, broadcast dst2 buffer too small (%llu %lu)\n",
							dst2_offset + (count * 4), radeon_bo_size(dst2_reloc->robj));
					return -EINVAL;
				}
				ib[idx+1] += (u32)(dst_reloc->gpu_offset >> 8);
				ib[idx+2] += (u32)(dst2_reloc->gpu_offset >> 8);
				ib[idx+8] += (u32)(src_reloc->gpu_offset & 0xfffffffc);
				ib[idx+9] += upper_32_bits(src_reloc->gpu_offset) & 0xff;
				p->idx += 10;
				break;
			default:
				DRM_ERROR("bad DMA_PACKET_COPY [%6d] 0x%08x invalid sub cmd\n", idx, header);
				return -EINVAL;
			}
			break;
		case DMA_PACKET_CONSTANT_FILL:
			r = r600_dma_cs_next_reloc(p, &dst_reloc);
			if (r) {
				DRM_ERROR("bad DMA_PACKET_CONSTANT_FILL\n");
				return -EINVAL;
			}
			dst_offset = radeon_get_ib_value(p, idx+1);
			dst_offset |= ((u64)(radeon_get_ib_value(p, idx+3) & 0x00ff0000)) << 16;
			if ((dst_offset + (count * 4)) > radeon_bo_size(dst_reloc->robj)) {
				dev_warn(p->dev, "DMA constant fill buffer too small (%llu %lu)\n",
					 dst_offset, radeon_bo_size(dst_reloc->robj));
				return -EINVAL;
			}
			ib[idx+1] += (u32)(dst_reloc->gpu_offset & 0xfffffffc);
			ib[idx+3] += (upper_32_bits(dst_reloc->gpu_offset) << 16) & 0x00ff0000;
			p->idx += 4;
			break;
		case DMA_PACKET_NOP:
			p->idx += 1;
			break;
		default:
			DRM_ERROR("Unknown packet type %d at %d !\n", cmd, idx);
			return -EINVAL;
		}
	} while (p->idx < p->chunk_ib->length_dw);
#if 0
	for (r = 0; r < p->ib->length_dw; r++) {
		pr_info("%05d  0x%08X\n", r, p->ib.ptr[r]);
		mdelay(1);
	}
#endif
	return 0;
}