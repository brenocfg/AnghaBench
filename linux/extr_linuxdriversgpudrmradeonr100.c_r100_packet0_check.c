#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_6__ {int* ptr; } ;
struct radeon_cs_parser {int cs_flags; scalar_t__ track; TYPE_1__ ib; } ;
struct radeon_cs_packet {int dummy; } ;
struct radeon_bo_list {int tiling_flags; int /*<<< orphan*/  gpu_offset; int /*<<< orphan*/  robj; } ;
struct TYPE_8__ {int offset; int pitch; int cpp; int /*<<< orphan*/  robj; } ;
struct r100_cs_track {int zb_dirty; int cb_dirty; int tex_dirty; int maxy; int z_enabled; int num_texture; int vap_vf_cntl; TYPE_5__* textures; int /*<<< orphan*/  vtx_size; TYPE_3__ zb; TYPE_2__* cb; } ;
struct TYPE_10__ {int enabled; int width; int height; int num_levels; int roundup_w; int roundup_h; int use_pitch; int tex_coord_type; int cpp; TYPE_4__* cube_info; void* compress_format; int /*<<< orphan*/  pitch; int /*<<< orphan*/  robj; } ;
struct TYPE_9__ {int offset; int width; int height; int /*<<< orphan*/  robj; } ;
struct TYPE_7__ {int offset; int pitch; int cpp; int /*<<< orphan*/  robj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,...) ; 
 int EINVAL ; 
 void* R100_TRACK_COMP_DXT1 ; 
 void* R100_TRACK_COMP_DXT35 ; 
 void* R100_TRACK_COMP_NONE ; 
 int RADEON_COLORPITCH_MASK ; 
 int RADEON_COLOR_MICROTILE_ENABLE ; 
 int RADEON_COLOR_TILE_ENABLE ; 
#define  RADEON_CRTC_GUI_TRIG_VLINE 193 
 int RADEON_CS_KEEP_TILING_FLAGS ; 
 int RADEON_DEPTHPITCH_MASK ; 
#define  RADEON_DST_PITCH_OFFSET 192 
 int RADEON_MAX_MIP_LEVEL_MASK ; 
 int RADEON_MAX_MIP_LEVEL_SHIFT ; 
#define  RADEON_PP_CNTL 191 
#define  RADEON_PP_CUBIC_FACES_0 190 
#define  RADEON_PP_CUBIC_FACES_1 189 
#define  RADEON_PP_CUBIC_FACES_2 188 
#define  RADEON_PP_CUBIC_OFFSET_T0_0 187 
#define  RADEON_PP_CUBIC_OFFSET_T0_1 186 
#define  RADEON_PP_CUBIC_OFFSET_T0_2 185 
#define  RADEON_PP_CUBIC_OFFSET_T0_3 184 
#define  RADEON_PP_CUBIC_OFFSET_T0_4 183 
#define  RADEON_PP_CUBIC_OFFSET_T1_0 182 
#define  RADEON_PP_CUBIC_OFFSET_T1_1 181 
#define  RADEON_PP_CUBIC_OFFSET_T1_2 180 
#define  RADEON_PP_CUBIC_OFFSET_T1_3 179 
#define  RADEON_PP_CUBIC_OFFSET_T1_4 178 
#define  RADEON_PP_CUBIC_OFFSET_T2_0 177 
#define  RADEON_PP_CUBIC_OFFSET_T2_1 176 
#define  RADEON_PP_CUBIC_OFFSET_T2_2 175 
#define  RADEON_PP_CUBIC_OFFSET_T2_3 174 
#define  RADEON_PP_CUBIC_OFFSET_T2_4 173 
#define  RADEON_PP_TEX_PITCH_0 172 
#define  RADEON_PP_TEX_PITCH_1 171 
#define  RADEON_PP_TEX_PITCH_2 170 
#define  RADEON_PP_TEX_SIZE_0 169 
#define  RADEON_PP_TEX_SIZE_1 168 
#define  RADEON_PP_TEX_SIZE_2 167 
#define  RADEON_PP_TXFILTER_0 166 
#define  RADEON_PP_TXFILTER_1 165 
#define  RADEON_PP_TXFILTER_2 164 
#define  RADEON_PP_TXFORMAT_0 163 
#define  RADEON_PP_TXFORMAT_1 162 
#define  RADEON_PP_TXFORMAT_2 161 
#define  RADEON_PP_TXOFFSET_0 160 
#define  RADEON_PP_TXOFFSET_1 159 
#define  RADEON_PP_TXOFFSET_2 158 
#define  RADEON_RB3D_CNTL 157 
#define  RADEON_RB3D_COLOROFFSET 156 
#define  RADEON_RB3D_COLORPITCH 155 
 int RADEON_RB3D_COLOR_FORMAT_SHIFT ; 
#define  RADEON_RB3D_DEPTHOFFSET 154 
#define  RADEON_RB3D_DEPTHPITCH 153 
#define  RADEON_RB3D_ZPASS_ADDR 152 
#define  RADEON_RB3D_ZSTENCILCNTL 151 
#define  RADEON_RE_WIDTH_HEIGHT 150 
#define  RADEON_SE_VF_CNTL 149 
#define  RADEON_SE_VTX_FMT 148 
#define  RADEON_SRC_PITCH_OFFSET 147 
 int RADEON_TEX_USIZE_MASK ; 
 int RADEON_TEX_VSIZE_MASK ; 
 int RADEON_TEX_VSIZE_SHIFT ; 
 int RADEON_TILING_MACRO ; 
 int RADEON_TILING_MICRO ; 
#define  RADEON_TXFORMAT_AI88 146 
#define  RADEON_TXFORMAT_ARGB1555 145 
#define  RADEON_TXFORMAT_ARGB4444 144 
#define  RADEON_TXFORMAT_ARGB8888 143 
 int RADEON_TXFORMAT_CUBIC_MAP_ENABLE ; 
#define  RADEON_TXFORMAT_DUDV88 142 
#define  RADEON_TXFORMAT_DXT1 141 
#define  RADEON_TXFORMAT_DXT23 140 
#define  RADEON_TXFORMAT_DXT45 139 
 int RADEON_TXFORMAT_FORMAT_MASK ; 
 int RADEON_TXFORMAT_HEIGHT_MASK ; 
 int RADEON_TXFORMAT_HEIGHT_SHIFT ; 
#define  RADEON_TXFORMAT_I8 138 
#define  RADEON_TXFORMAT_LDUDUV8888 137 
#define  RADEON_TXFORMAT_LDUDV655 136 
 int RADEON_TXFORMAT_NON_POWER2 ; 
#define  RADEON_TXFORMAT_RGB332 135 
#define  RADEON_TXFORMAT_RGB565 134 
#define  RADEON_TXFORMAT_RGBA8888 133 
#define  RADEON_TXFORMAT_SHADOW16 132 
#define  RADEON_TXFORMAT_SHADOW32 131 
#define  RADEON_TXFORMAT_VYUY422 130 
 int RADEON_TXFORMAT_WIDTH_MASK ; 
 int RADEON_TXFORMAT_WIDTH_SHIFT ; 
#define  RADEON_TXFORMAT_Y8 129 
#define  RADEON_TXFORMAT_YVYU422 128 
 int RADEON_TXO_MACRO_TILE ; 
 int RADEON_TXO_MICRO_TILE_X2 ; 
 int RADEON_Z_ENABLE ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 
 int r100_cs_packet_parse_vline (struct radeon_cs_parser*) ; 
 int /*<<< orphan*/  r100_get_vtx_size (int) ; 
 int r100_reloc_pitch_offset (struct radeon_cs_parser*,struct radeon_cs_packet*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  radeon_cs_dump_packet (struct radeon_cs_parser*,struct radeon_cs_packet*) ; 
 int radeon_cs_packet_next_reloc (struct radeon_cs_parser*,struct radeon_bo_list**,int /*<<< orphan*/ ) ; 
 int radeon_get_ib_value (struct radeon_cs_parser*,unsigned int) ; 

__attribute__((used)) static int r100_packet0_check(struct radeon_cs_parser *p,
			      struct radeon_cs_packet *pkt,
			      unsigned idx, unsigned reg)
{
	struct radeon_bo_list *reloc;
	struct r100_cs_track *track;
	volatile uint32_t *ib;
	uint32_t tmp;
	int r;
	int i, face;
	u32 tile_flags = 0;
	u32 idx_value;

	ib = p->ib.ptr;
	track = (struct r100_cs_track *)p->track;

	idx_value = radeon_get_ib_value(p, idx);

	switch (reg) {
	case RADEON_CRTC_GUI_TRIG_VLINE:
		r = r100_cs_packet_parse_vline(p);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		break;
		/* FIXME: only allow PACKET3 blit? easier to check for out of
		 * range access */
	case RADEON_DST_PITCH_OFFSET:
	case RADEON_SRC_PITCH_OFFSET:
		r = r100_reloc_pitch_offset(p, pkt, idx, reg);
		if (r)
			return r;
		break;
	case RADEON_RB3D_DEPTHOFFSET:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		track->zb.robj = reloc->robj;
		track->zb.offset = idx_value;
		track->zb_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		break;
	case RADEON_RB3D_COLOROFFSET:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		track->cb[0].robj = reloc->robj;
		track->cb[0].offset = idx_value;
		track->cb_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		break;
	case RADEON_PP_TXOFFSET_0:
	case RADEON_PP_TXOFFSET_1:
	case RADEON_PP_TXOFFSET_2:
		i = (reg - RADEON_PP_TXOFFSET_0) / 24;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		if (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) {
			if (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= RADEON_TXO_MACRO_TILE;
			if (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= RADEON_TXO_MICRO_TILE_X2;

			tmp = idx_value & ~(0x7 << 2);
			tmp |= tile_flags;
			ib[idx] = tmp + ((u32)reloc->gpu_offset);
		} else
			ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[i].robj = reloc->robj;
		track->tex_dirty = true;
		break;
	case RADEON_PP_CUBIC_OFFSET_T0_0:
	case RADEON_PP_CUBIC_OFFSET_T0_1:
	case RADEON_PP_CUBIC_OFFSET_T0_2:
	case RADEON_PP_CUBIC_OFFSET_T0_3:
	case RADEON_PP_CUBIC_OFFSET_T0_4:
		i = (reg - RADEON_PP_CUBIC_OFFSET_T0_0) / 4;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		track->textures[0].cube_info[i].offset = idx_value;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[0].cube_info[i].robj = reloc->robj;
		track->tex_dirty = true;
		break;
	case RADEON_PP_CUBIC_OFFSET_T1_0:
	case RADEON_PP_CUBIC_OFFSET_T1_1:
	case RADEON_PP_CUBIC_OFFSET_T1_2:
	case RADEON_PP_CUBIC_OFFSET_T1_3:
	case RADEON_PP_CUBIC_OFFSET_T1_4:
		i = (reg - RADEON_PP_CUBIC_OFFSET_T1_0) / 4;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		track->textures[1].cube_info[i].offset = idx_value;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[1].cube_info[i].robj = reloc->robj;
		track->tex_dirty = true;
		break;
	case RADEON_PP_CUBIC_OFFSET_T2_0:
	case RADEON_PP_CUBIC_OFFSET_T2_1:
	case RADEON_PP_CUBIC_OFFSET_T2_2:
	case RADEON_PP_CUBIC_OFFSET_T2_3:
	case RADEON_PP_CUBIC_OFFSET_T2_4:
		i = (reg - RADEON_PP_CUBIC_OFFSET_T2_0) / 4;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		track->textures[2].cube_info[i].offset = idx_value;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[2].cube_info[i].robj = reloc->robj;
		track->tex_dirty = true;
		break;
	case RADEON_RE_WIDTH_HEIGHT:
		track->maxy = ((idx_value >> 16) & 0x7FF);
		track->cb_dirty = true;
		track->zb_dirty = true;
		break;
	case RADEON_RB3D_COLORPITCH:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		if (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) {
			if (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= RADEON_COLOR_TILE_ENABLE;
			if (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= RADEON_COLOR_MICROTILE_ENABLE;

			tmp = idx_value & ~(0x7 << 16);
			tmp |= tile_flags;
			ib[idx] = tmp;
		} else
			ib[idx] = idx_value;

		track->cb[0].pitch = idx_value & RADEON_COLORPITCH_MASK;
		track->cb_dirty = true;
		break;
	case RADEON_RB3D_DEPTHPITCH:
		track->zb.pitch = idx_value & RADEON_DEPTHPITCH_MASK;
		track->zb_dirty = true;
		break;
	case RADEON_RB3D_CNTL:
		switch ((idx_value >> RADEON_RB3D_COLOR_FORMAT_SHIFT) & 0x1f) {
		case 7:
		case 8:
		case 9:
		case 11:
		case 12:
			track->cb[0].cpp = 1;
			break;
		case 3:
		case 4:
		case 15:
			track->cb[0].cpp = 2;
			break;
		case 6:
			track->cb[0].cpp = 4;
			break;
		default:
			DRM_ERROR("Invalid color buffer format (%d) !\n",
				  ((idx_value >> RADEON_RB3D_COLOR_FORMAT_SHIFT) & 0x1f));
			return -EINVAL;
		}
		track->z_enabled = !!(idx_value & RADEON_Z_ENABLE);
		track->cb_dirty = true;
		track->zb_dirty = true;
		break;
	case RADEON_RB3D_ZSTENCILCNTL:
		switch (idx_value & 0xf) {
		case 0:
			track->zb.cpp = 2;
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 9:
		case 11:
			track->zb.cpp = 4;
			break;
		default:
			break;
		}
		track->zb_dirty = true;
		break;
	case RADEON_RB3D_ZPASS_ADDR:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		break;
	case RADEON_PP_CNTL:
		{
			uint32_t temp = idx_value >> 4;
			for (i = 0; i < track->num_texture; i++)
				track->textures[i].enabled = !!(temp & (1 << i));
			track->tex_dirty = true;
		}
		break;
	case RADEON_SE_VF_CNTL:
		track->vap_vf_cntl = idx_value;
		break;
	case RADEON_SE_VTX_FMT:
		track->vtx_size = r100_get_vtx_size(idx_value);
		break;
	case RADEON_PP_TEX_SIZE_0:
	case RADEON_PP_TEX_SIZE_1:
	case RADEON_PP_TEX_SIZE_2:
		i = (reg - RADEON_PP_TEX_SIZE_0) / 8;
		track->textures[i].width = (idx_value & RADEON_TEX_USIZE_MASK) + 1;
		track->textures[i].height = ((idx_value & RADEON_TEX_VSIZE_MASK) >> RADEON_TEX_VSIZE_SHIFT) + 1;
		track->tex_dirty = true;
		break;
	case RADEON_PP_TEX_PITCH_0:
	case RADEON_PP_TEX_PITCH_1:
	case RADEON_PP_TEX_PITCH_2:
		i = (reg - RADEON_PP_TEX_PITCH_0) / 8;
		track->textures[i].pitch = idx_value + 32;
		track->tex_dirty = true;
		break;
	case RADEON_PP_TXFILTER_0:
	case RADEON_PP_TXFILTER_1:
	case RADEON_PP_TXFILTER_2:
		i = (reg - RADEON_PP_TXFILTER_0) / 24;
		track->textures[i].num_levels = ((idx_value & RADEON_MAX_MIP_LEVEL_MASK)
						 >> RADEON_MAX_MIP_LEVEL_SHIFT);
		tmp = (idx_value >> 23) & 0x7;
		if (tmp == 2 || tmp == 6)
			track->textures[i].roundup_w = false;
		tmp = (idx_value >> 27) & 0x7;
		if (tmp == 2 || tmp == 6)
			track->textures[i].roundup_h = false;
		track->tex_dirty = true;
		break;
	case RADEON_PP_TXFORMAT_0:
	case RADEON_PP_TXFORMAT_1:
	case RADEON_PP_TXFORMAT_2:
		i = (reg - RADEON_PP_TXFORMAT_0) / 24;
		if (idx_value & RADEON_TXFORMAT_NON_POWER2) {
			track->textures[i].use_pitch = 1;
		} else {
			track->textures[i].use_pitch = 0;
			track->textures[i].width = 1 << ((idx_value >> RADEON_TXFORMAT_WIDTH_SHIFT) & RADEON_TXFORMAT_WIDTH_MASK);
			track->textures[i].height = 1 << ((idx_value >> RADEON_TXFORMAT_HEIGHT_SHIFT) & RADEON_TXFORMAT_HEIGHT_MASK);
		}
		if (idx_value & RADEON_TXFORMAT_CUBIC_MAP_ENABLE)
			track->textures[i].tex_coord_type = 2;
		switch ((idx_value & RADEON_TXFORMAT_FORMAT_MASK)) {
		case RADEON_TXFORMAT_I8:
		case RADEON_TXFORMAT_RGB332:
		case RADEON_TXFORMAT_Y8:
			track->textures[i].cpp = 1;
			track->textures[i].compress_format = R100_TRACK_COMP_NONE;
			break;
		case RADEON_TXFORMAT_AI88:
		case RADEON_TXFORMAT_ARGB1555:
		case RADEON_TXFORMAT_RGB565:
		case RADEON_TXFORMAT_ARGB4444:
		case RADEON_TXFORMAT_VYUY422:
		case RADEON_TXFORMAT_YVYU422:
		case RADEON_TXFORMAT_SHADOW16:
		case RADEON_TXFORMAT_LDUDV655:
		case RADEON_TXFORMAT_DUDV88:
			track->textures[i].cpp = 2;
			track->textures[i].compress_format = R100_TRACK_COMP_NONE;
			break;
		case RADEON_TXFORMAT_ARGB8888:
		case RADEON_TXFORMAT_RGBA8888:
		case RADEON_TXFORMAT_SHADOW32:
		case RADEON_TXFORMAT_LDUDUV8888:
			track->textures[i].cpp = 4;
			track->textures[i].compress_format = R100_TRACK_COMP_NONE;
			break;
		case RADEON_TXFORMAT_DXT1:
			track->textures[i].cpp = 1;
			track->textures[i].compress_format = R100_TRACK_COMP_DXT1;
			break;
		case RADEON_TXFORMAT_DXT23:
		case RADEON_TXFORMAT_DXT45:
			track->textures[i].cpp = 1;
			track->textures[i].compress_format = R100_TRACK_COMP_DXT35;
			break;
		}
		track->textures[i].cube_info[4].width = 1 << ((idx_value >> 16) & 0xf);
		track->textures[i].cube_info[4].height = 1 << ((idx_value >> 20) & 0xf);
		track->tex_dirty = true;
		break;
	case RADEON_PP_CUBIC_FACES_0:
	case RADEON_PP_CUBIC_FACES_1:
	case RADEON_PP_CUBIC_FACES_2:
		tmp = idx_value;
		i = (reg - RADEON_PP_CUBIC_FACES_0) / 4;
		for (face = 0; face < 4; face++) {
			track->textures[i].cube_info[face].width = 1 << ((tmp >> (face * 8)) & 0xf);
			track->textures[i].cube_info[face].height = 1 << ((tmp >> ((face * 8) + 4)) & 0xf);
		}
		track->tex_dirty = true;
		break;
	default:
		pr_err("Forbidden register 0x%04X in cs at %d\n", reg, idx);
		return -EINVAL;
	}
	return 0;
}