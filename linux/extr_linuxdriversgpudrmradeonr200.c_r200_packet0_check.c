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
struct r100_cs_track {int zb_dirty; int cb_dirty; int tex_dirty; int maxy; int z_enabled; int num_texture; int vap_vf_cntl; int max_indx; TYPE_5__* textures; int /*<<< orphan*/  vtx_size; TYPE_3__ zb; TYPE_2__* cb; } ;
struct TYPE_10__ {int enabled; int width; int height; int num_levels; int roundup_w; int roundup_h; int txdepth; int tex_coord_type; int use_pitch; int lookup_disable; int cpp; TYPE_4__* cube_info; void* compress_format; int /*<<< orphan*/  pitch; int /*<<< orphan*/  robj; } ;
struct TYPE_9__ {int offset; int width; int height; int /*<<< orphan*/  robj; } ;
struct TYPE_7__ {int offset; int pitch; int cpp; int /*<<< orphan*/  robj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 void* R100_TRACK_COMP_DXT1 ; 
 void* R100_TRACK_COMP_NONE ; 
 int R200_MAX_MIP_LEVEL_MASK ; 
 int R200_MAX_MIP_LEVEL_SHIFT ; 
#define  R200_PP_CUBIC_FACES_0 240 
#define  R200_PP_CUBIC_FACES_1 239 
#define  R200_PP_CUBIC_FACES_2 238 
#define  R200_PP_CUBIC_FACES_3 237 
#define  R200_PP_CUBIC_FACES_4 236 
#define  R200_PP_CUBIC_FACES_5 235 
#define  R200_PP_CUBIC_OFFSET_F1_0 234 
#define  R200_PP_CUBIC_OFFSET_F1_1 233 
#define  R200_PP_CUBIC_OFFSET_F1_2 232 
#define  R200_PP_CUBIC_OFFSET_F1_3 231 
#define  R200_PP_CUBIC_OFFSET_F1_4 230 
#define  R200_PP_CUBIC_OFFSET_F1_5 229 
#define  R200_PP_CUBIC_OFFSET_F2_0 228 
#define  R200_PP_CUBIC_OFFSET_F2_1 227 
#define  R200_PP_CUBIC_OFFSET_F2_2 226 
#define  R200_PP_CUBIC_OFFSET_F2_3 225 
#define  R200_PP_CUBIC_OFFSET_F2_4 224 
#define  R200_PP_CUBIC_OFFSET_F2_5 223 
#define  R200_PP_CUBIC_OFFSET_F3_0 222 
#define  R200_PP_CUBIC_OFFSET_F3_1 221 
#define  R200_PP_CUBIC_OFFSET_F3_2 220 
#define  R200_PP_CUBIC_OFFSET_F3_3 219 
#define  R200_PP_CUBIC_OFFSET_F3_4 218 
#define  R200_PP_CUBIC_OFFSET_F3_5 217 
#define  R200_PP_CUBIC_OFFSET_F4_0 216 
#define  R200_PP_CUBIC_OFFSET_F4_1 215 
#define  R200_PP_CUBIC_OFFSET_F4_2 214 
#define  R200_PP_CUBIC_OFFSET_F4_3 213 
#define  R200_PP_CUBIC_OFFSET_F4_4 212 
#define  R200_PP_CUBIC_OFFSET_F4_5 211 
#define  R200_PP_CUBIC_OFFSET_F5_0 210 
#define  R200_PP_CUBIC_OFFSET_F5_1 209 
#define  R200_PP_CUBIC_OFFSET_F5_2 208 
#define  R200_PP_CUBIC_OFFSET_F5_3 207 
#define  R200_PP_CUBIC_OFFSET_F5_4 206 
#define  R200_PP_CUBIC_OFFSET_F5_5 205 
#define  R200_PP_TXFILTER_0 204 
#define  R200_PP_TXFILTER_1 203 
#define  R200_PP_TXFILTER_2 202 
#define  R200_PP_TXFILTER_3 201 
#define  R200_PP_TXFILTER_4 200 
#define  R200_PP_TXFILTER_5 199 
#define  R200_PP_TXFORMAT_0 198 
#define  R200_PP_TXFORMAT_1 197 
#define  R200_PP_TXFORMAT_2 196 
#define  R200_PP_TXFORMAT_3 195 
#define  R200_PP_TXFORMAT_4 194 
#define  R200_PP_TXFORMAT_5 193 
#define  R200_PP_TXFORMAT_X_0 192 
#define  R200_PP_TXFORMAT_X_1 191 
#define  R200_PP_TXFORMAT_X_2 190 
#define  R200_PP_TXFORMAT_X_3 189 
#define  R200_PP_TXFORMAT_X_4 188 
#define  R200_PP_TXFORMAT_X_5 187 
#define  R200_PP_TXMULTI_CTL_0 186 
#define  R200_PP_TXMULTI_CTL_1 185 
#define  R200_PP_TXMULTI_CTL_2 184 
#define  R200_PP_TXMULTI_CTL_3 183 
#define  R200_PP_TXMULTI_CTL_4 182 
#define  R200_PP_TXMULTI_CTL_5 181 
#define  R200_PP_TXOFFSET_0 180 
#define  R200_PP_TXOFFSET_1 179 
#define  R200_PP_TXOFFSET_2 178 
#define  R200_PP_TXOFFSET_3 177 
#define  R200_PP_TXOFFSET_4 176 
#define  R200_PP_TXOFFSET_5 175 
#define  R200_PP_TXPITCH_0 174 
#define  R200_PP_TXPITCH_1 173 
#define  R200_PP_TXPITCH_2 172 
#define  R200_PP_TXPITCH_3 171 
#define  R200_PP_TXPITCH_4 170 
#define  R200_PP_TXPITCH_5 169 
#define  R200_PP_TXSIZE_0 168 
#define  R200_PP_TXSIZE_1 167 
#define  R200_PP_TXSIZE_2 166 
#define  R200_PP_TXSIZE_3 165 
#define  R200_PP_TXSIZE_4 164 
#define  R200_PP_TXSIZE_5 163 
#define  R200_SE_VTX_FMT_0 162 
#define  R200_SE_VTX_FMT_1 161 
#define  R200_TXFORMAT_ABGR8888 160 
#define  R200_TXFORMAT_AI88 159 
#define  R200_TXFORMAT_ARGB1555 158 
#define  R200_TXFORMAT_ARGB4444 157 
#define  R200_TXFORMAT_ARGB8888 156 
#define  R200_TXFORMAT_AVYU4444 155 
#define  R200_TXFORMAT_BGR111110 154 
#define  R200_TXFORMAT_DVDU88 153 
#define  R200_TXFORMAT_DXT1 152 
#define  R200_TXFORMAT_DXT23 151 
#define  R200_TXFORMAT_DXT45 150 
#define  R200_TXFORMAT_I8 149 
#define  R200_TXFORMAT_LDVDU655 148 
#define  R200_TXFORMAT_LDVDU8888 147 
 int R200_TXFORMAT_LOOKUP_DISABLE ; 
 int R200_TXFORMAT_NON_POWER2 ; 
#define  R200_TXFORMAT_RGB332 146 
#define  R200_TXFORMAT_RGB565 145 
#define  R200_TXFORMAT_RGBA8888 144 
#define  R200_TXFORMAT_VYUY422 143 
#define  R200_TXFORMAT_Y8 142 
#define  R200_TXFORMAT_YVYU422 141 
 int R200_TXO_MACRO_TILE ; 
 int R200_TXO_MICRO_TILE ; 
 int RADEON_COLORPITCH_MASK ; 
 int RADEON_COLOR_MICROTILE_ENABLE ; 
 int RADEON_COLOR_TILE_ENABLE ; 
#define  RADEON_CRTC_GUI_TRIG_VLINE 140 
 int RADEON_CS_KEEP_TILING_FLAGS ; 
 int RADEON_DEPTHPITCH_MASK ; 
 int RADEON_DEPTHXY_OFFSET_ENABLE ; 
#define  RADEON_DST_PITCH_OFFSET 139 
#define  RADEON_PP_CNTL 138 
#define  RADEON_RB3D_CNTL 137 
#define  RADEON_RB3D_COLOROFFSET 136 
#define  RADEON_RB3D_COLORPITCH 135 
 int RADEON_RB3D_COLOR_FORMAT_SHIFT ; 
#define  RADEON_RB3D_DEPTHOFFSET 134 
#define  RADEON_RB3D_DEPTHPITCH 133 
#define  RADEON_RB3D_ZPASS_ADDR 132 
#define  RADEON_RB3D_ZSTENCILCNTL 131 
#define  RADEON_RE_WIDTH_HEIGHT 130 
#define  RADEON_SE_VF_CNTL 129 
#define  RADEON_SRC_PITCH_OFFSET 128 
 int RADEON_TEX_USIZE_MASK ; 
 int RADEON_TEX_VSIZE_MASK ; 
 int RADEON_TEX_VSIZE_SHIFT ; 
 int RADEON_TILING_MACRO ; 
 int RADEON_TILING_MICRO ; 
 int RADEON_TXFORMAT_FORMAT_MASK ; 
 int RADEON_TXFORMAT_HEIGHT_MASK ; 
 int RADEON_TXFORMAT_HEIGHT_SHIFT ; 
 int RADEON_TXFORMAT_WIDTH_MASK ; 
 int RADEON_TXFORMAT_WIDTH_SHIFT ; 
 int RADEON_Z_ENABLE ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 
 int r100_cs_packet_parse_vline (struct radeon_cs_parser*) ; 
 int r100_reloc_pitch_offset (struct radeon_cs_parser*,struct radeon_cs_packet*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  r200_get_vtx_size_0 (int) ; 
 int /*<<< orphan*/  r200_get_vtx_size_1 (int) ; 
 int /*<<< orphan*/  radeon_cs_dump_packet (struct radeon_cs_parser*,struct radeon_cs_packet*) ; 
 int radeon_cs_packet_next_reloc (struct radeon_cs_parser*,struct radeon_bo_list**,int /*<<< orphan*/ ) ; 
 int radeon_get_ib_value (struct radeon_cs_parser*,unsigned int) ; 

int r200_packet0_check(struct radeon_cs_parser *p,
		       struct radeon_cs_packet *pkt,
		       unsigned idx, unsigned reg)
{
	struct radeon_bo_list *reloc;
	struct r100_cs_track *track;
	volatile uint32_t *ib;
	uint32_t tmp;
	int r;
	int i;
	int face;
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
	case R200_PP_TXOFFSET_0:
	case R200_PP_TXOFFSET_1:
	case R200_PP_TXOFFSET_2:
	case R200_PP_TXOFFSET_3:
	case R200_PP_TXOFFSET_4:
	case R200_PP_TXOFFSET_5:
		i = (reg - R200_PP_TXOFFSET_0) / 24;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		if (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) {
			if (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= R200_TXO_MACRO_TILE;
			if (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= R200_TXO_MICRO_TILE;

			tmp = idx_value & ~(0x7 << 2);
			tmp |= tile_flags;
			ib[idx] = tmp + ((u32)reloc->gpu_offset);
		} else
			ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[i].robj = reloc->robj;
		track->tex_dirty = true;
		break;
	case R200_PP_CUBIC_OFFSET_F1_0:
	case R200_PP_CUBIC_OFFSET_F2_0:
	case R200_PP_CUBIC_OFFSET_F3_0:
	case R200_PP_CUBIC_OFFSET_F4_0:
	case R200_PP_CUBIC_OFFSET_F5_0:
	case R200_PP_CUBIC_OFFSET_F1_1:
	case R200_PP_CUBIC_OFFSET_F2_1:
	case R200_PP_CUBIC_OFFSET_F3_1:
	case R200_PP_CUBIC_OFFSET_F4_1:
	case R200_PP_CUBIC_OFFSET_F5_1:
	case R200_PP_CUBIC_OFFSET_F1_2:
	case R200_PP_CUBIC_OFFSET_F2_2:
	case R200_PP_CUBIC_OFFSET_F3_2:
	case R200_PP_CUBIC_OFFSET_F4_2:
	case R200_PP_CUBIC_OFFSET_F5_2:
	case R200_PP_CUBIC_OFFSET_F1_3:
	case R200_PP_CUBIC_OFFSET_F2_3:
	case R200_PP_CUBIC_OFFSET_F3_3:
	case R200_PP_CUBIC_OFFSET_F4_3:
	case R200_PP_CUBIC_OFFSET_F5_3:
	case R200_PP_CUBIC_OFFSET_F1_4:
	case R200_PP_CUBIC_OFFSET_F2_4:
	case R200_PP_CUBIC_OFFSET_F3_4:
	case R200_PP_CUBIC_OFFSET_F4_4:
	case R200_PP_CUBIC_OFFSET_F5_4:
	case R200_PP_CUBIC_OFFSET_F1_5:
	case R200_PP_CUBIC_OFFSET_F2_5:
	case R200_PP_CUBIC_OFFSET_F3_5:
	case R200_PP_CUBIC_OFFSET_F4_5:
	case R200_PP_CUBIC_OFFSET_F5_5:
		i = (reg - R200_PP_TXOFFSET_0) / 24;
		face = (reg - ((i * 24) + R200_PP_TXOFFSET_0)) / 4;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		track->textures[i].cube_info[face - 1].offset = idx_value;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[i].cube_info[face - 1].robj = reloc->robj;
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
		if (idx_value & RADEON_DEPTHXY_OFFSET_ENABLE) {
			DRM_ERROR("No support for depth xy offset in kms\n");
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
	case 0x210c:
		/* VAP_VF_MAX_VTX_INDX */
		track->max_indx = idx_value & 0x00FFFFFFUL;
		break;
	case R200_SE_VTX_FMT_0:
		track->vtx_size = r200_get_vtx_size_0(idx_value);
		break;
	case R200_SE_VTX_FMT_1:
		track->vtx_size += r200_get_vtx_size_1(idx_value);
		break;
	case R200_PP_TXSIZE_0:
	case R200_PP_TXSIZE_1:
	case R200_PP_TXSIZE_2:
	case R200_PP_TXSIZE_3:
	case R200_PP_TXSIZE_4:
	case R200_PP_TXSIZE_5:
		i = (reg - R200_PP_TXSIZE_0) / 32;
		track->textures[i].width = (idx_value & RADEON_TEX_USIZE_MASK) + 1;
		track->textures[i].height = ((idx_value & RADEON_TEX_VSIZE_MASK) >> RADEON_TEX_VSIZE_SHIFT) + 1;
		track->tex_dirty = true;
		break;
	case R200_PP_TXPITCH_0:
	case R200_PP_TXPITCH_1:
	case R200_PP_TXPITCH_2:
	case R200_PP_TXPITCH_3:
	case R200_PP_TXPITCH_4:
	case R200_PP_TXPITCH_5:
		i = (reg - R200_PP_TXPITCH_0) / 32;
		track->textures[i].pitch = idx_value + 32;
		track->tex_dirty = true;
		break;
	case R200_PP_TXFILTER_0:
	case R200_PP_TXFILTER_1:
	case R200_PP_TXFILTER_2:
	case R200_PP_TXFILTER_3:
	case R200_PP_TXFILTER_4:
	case R200_PP_TXFILTER_5:
		i = (reg - R200_PP_TXFILTER_0) / 32;
		track->textures[i].num_levels = ((idx_value & R200_MAX_MIP_LEVEL_MASK)
						 >> R200_MAX_MIP_LEVEL_SHIFT);
		tmp = (idx_value >> 23) & 0x7;
		if (tmp == 2 || tmp == 6)
			track->textures[i].roundup_w = false;
		tmp = (idx_value >> 27) & 0x7;
		if (tmp == 2 || tmp == 6)
			track->textures[i].roundup_h = false;
		track->tex_dirty = true;
		break;
	case R200_PP_TXMULTI_CTL_0:
	case R200_PP_TXMULTI_CTL_1:
	case R200_PP_TXMULTI_CTL_2:
	case R200_PP_TXMULTI_CTL_3:
	case R200_PP_TXMULTI_CTL_4:
	case R200_PP_TXMULTI_CTL_5:
		i = (reg - R200_PP_TXMULTI_CTL_0) / 32;
		break;
	case R200_PP_TXFORMAT_X_0:
	case R200_PP_TXFORMAT_X_1:
	case R200_PP_TXFORMAT_X_2:
	case R200_PP_TXFORMAT_X_3:
	case R200_PP_TXFORMAT_X_4:
	case R200_PP_TXFORMAT_X_5:
		i = (reg - R200_PP_TXFORMAT_X_0) / 32;
		track->textures[i].txdepth = idx_value & 0x7;
		tmp = (idx_value >> 16) & 0x3;
		/* 2D, 3D, CUBE */
		switch (tmp) {
		case 0:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			/* 1D/2D */
			track->textures[i].tex_coord_type = 0;
			break;
		case 1:
			/* CUBE */
			track->textures[i].tex_coord_type = 2;
			break;
		case 2:
			/* 3D */
			track->textures[i].tex_coord_type = 1;
			break;
		}
		track->tex_dirty = true;
		break;
	case R200_PP_TXFORMAT_0:
	case R200_PP_TXFORMAT_1:
	case R200_PP_TXFORMAT_2:
	case R200_PP_TXFORMAT_3:
	case R200_PP_TXFORMAT_4:
	case R200_PP_TXFORMAT_5:
		i = (reg - R200_PP_TXFORMAT_0) / 32;
		if (idx_value & R200_TXFORMAT_NON_POWER2) {
			track->textures[i].use_pitch = 1;
		} else {
			track->textures[i].use_pitch = 0;
			track->textures[i].width = 1 << ((idx_value >> RADEON_TXFORMAT_WIDTH_SHIFT) & RADEON_TXFORMAT_WIDTH_MASK);
			track->textures[i].height = 1 << ((idx_value >> RADEON_TXFORMAT_HEIGHT_SHIFT) & RADEON_TXFORMAT_HEIGHT_MASK);
		}
		if (idx_value & R200_TXFORMAT_LOOKUP_DISABLE)
			track->textures[i].lookup_disable = true;
		switch ((idx_value & RADEON_TXFORMAT_FORMAT_MASK)) {
		case R200_TXFORMAT_I8:
		case R200_TXFORMAT_RGB332:
		case R200_TXFORMAT_Y8:
			track->textures[i].cpp = 1;
			track->textures[i].compress_format = R100_TRACK_COMP_NONE;
			break;
		case R200_TXFORMAT_AI88:
		case R200_TXFORMAT_ARGB1555:
		case R200_TXFORMAT_RGB565:
		case R200_TXFORMAT_ARGB4444:
		case R200_TXFORMAT_VYUY422:
		case R200_TXFORMAT_YVYU422:
		case R200_TXFORMAT_LDVDU655:
		case R200_TXFORMAT_DVDU88:
		case R200_TXFORMAT_AVYU4444:
			track->textures[i].cpp = 2;
			track->textures[i].compress_format = R100_TRACK_COMP_NONE;
			break;
		case R200_TXFORMAT_ARGB8888:
		case R200_TXFORMAT_RGBA8888:
		case R200_TXFORMAT_ABGR8888:
		case R200_TXFORMAT_BGR111110:
		case R200_TXFORMAT_LDVDU8888:
			track->textures[i].cpp = 4;
			track->textures[i].compress_format = R100_TRACK_COMP_NONE;
			break;
		case R200_TXFORMAT_DXT1:
			track->textures[i].cpp = 1;
			track->textures[i].compress_format = R100_TRACK_COMP_DXT1;
			break;
		case R200_TXFORMAT_DXT23:
		case R200_TXFORMAT_DXT45:
			track->textures[i].cpp = 1;
			track->textures[i].compress_format = R100_TRACK_COMP_DXT1;
			break;
		}
		track->textures[i].cube_info[4].width = 1 << ((idx_value >> 16) & 0xf);
		track->textures[i].cube_info[4].height = 1 << ((idx_value >> 20) & 0xf);
		track->tex_dirty = true;
		break;
	case R200_PP_CUBIC_FACES_0:
	case R200_PP_CUBIC_FACES_1:
	case R200_PP_CUBIC_FACES_2:
	case R200_PP_CUBIC_FACES_3:
	case R200_PP_CUBIC_FACES_4:
	case R200_PP_CUBIC_FACES_5:
		tmp = idx_value;
		i = (reg - R200_PP_CUBIC_FACES_0) / 32;
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