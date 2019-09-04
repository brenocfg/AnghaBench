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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int* ptr; } ;
struct radeon_cs_parser {int cs_flags; int /*<<< orphan*/  dev; TYPE_1__ ib; scalar_t__ track; } ;
struct radeon_bo_list {int gpu_offset; int tiling_flags; int /*<<< orphan*/  robj; } ;
struct r600_cs_track {int sq_config; int db_depth_control; int db_dirty; int db_depth_info; int db_depth_view; int db_depth_size; int db_depth_size_idx; int vgt_strmout_en; int streamout_dirty; int vgt_strmout_buffer_en; int* vgt_strmout_bo_offset; int* vgt_strmout_bo_mc; int* vgt_strmout_size; int cb_target_mask; int cb_dirty; int cb_shader_mask; int log_nsamples; int nsamples; int is_resolve; int* cb_color_info; int* cb_color_view; int* cb_color_size; int* cb_color_size_idx; int* cb_color_base_last; int* cb_color_frag_offset; int* cb_color_bo_offset; int* cb_color_tile_offset; int* cb_color_mask; int* cb_color_bo_mc; int db_offset; int db_bo_mc; int htile_offset; int htile_surface; int sx_misc_kill_all_prims; int /*<<< orphan*/  htile_bo; int /*<<< orphan*/  db_bo; int /*<<< orphan*/ * cb_color_bo; int /*<<< orphan*/ * cb_color_tile_bo; int /*<<< orphan*/ * cb_color_frag_bo; int /*<<< orphan*/ * vgt_strmout_bo; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
#define  CB_COLOR0_BASE 284 
#define  CB_COLOR1_BASE 283 
#define  CB_COLOR2_BASE 282 
#define  CB_COLOR3_BASE 281 
#define  CB_COLOR4_BASE 280 
#define  CB_COLOR5_BASE 279 
#define  CB_COLOR6_BASE 278 
#define  CB_COLOR7_BASE 277 
#define  CP_COHER_BASE 276 
 int C_028010_ARRAY_MODE ; 
#define  DB_DEPTH_BASE 275 
#define  DB_HTILE_DATA_BASE 274 
#define  DB_HTILE_SURFACE 273 
 int EINVAL ; 
 int /*<<< orphan*/  G_0280A0_TILE_MODE (int) ; 
 int G_028808_SPECIAL_OP (int) ; 
 int G_028C04_MSAA_NUM_SAMPLES (int) ; 
 int RADEON_CS_KEEP_TILING_FLAGS ; 
 int RADEON_TILING_MACRO ; 
 int RADEON_TILING_MICRO ; 
#define  R_008C44_SQ_ESGS_RING_SIZE 272 
#define  R_008C4C_SQ_GSVS_RING_SIZE 271 
#define  R_008C54_SQ_ESTMP_RING_SIZE 270 
#define  R_008C5C_SQ_GSTMP_RING_SIZE 269 
#define  R_008C64_SQ_VSTMP_RING_SIZE 268 
#define  R_008C6C_SQ_PSTMP_RING_SIZE 267 
#define  R_008C74_SQ_FBUF_RING_SIZE 266 
#define  R_008C7C_SQ_REDUC_RING_SIZE 265 
#define  R_028000_DB_DEPTH_SIZE 264 
#define  R_028004_DB_DEPTH_VIEW 263 
#define  R_028010_DB_DEPTH_INFO 262 
#define  R_028060_CB_COLOR0_SIZE 261 
#define  R_028064_CB_COLOR1_SIZE 260 
#define  R_028068_CB_COLOR2_SIZE 259 
#define  R_02806C_CB_COLOR3_SIZE 258 
#define  R_028070_CB_COLOR4_SIZE 257 
#define  R_028074_CB_COLOR5_SIZE 256 
#define  R_028078_CB_COLOR6_SIZE 255 
#define  R_02807C_CB_COLOR7_SIZE 254 
#define  R_028080_CB_COLOR0_VIEW 253 
#define  R_028084_CB_COLOR1_VIEW 252 
#define  R_028088_CB_COLOR2_VIEW 251 
#define  R_02808C_CB_COLOR3_VIEW 250 
#define  R_028090_CB_COLOR4_VIEW 249 
#define  R_028094_CB_COLOR5_VIEW 248 
#define  R_028098_CB_COLOR6_VIEW 247 
#define  R_02809C_CB_COLOR7_VIEW 246 
#define  R_0280A0_CB_COLOR0_INFO 245 
#define  R_0280A4_CB_COLOR1_INFO 244 
#define  R_0280A8_CB_COLOR2_INFO 243 
#define  R_0280AC_CB_COLOR3_INFO 242 
#define  R_0280B0_CB_COLOR4_INFO 241 
#define  R_0280B4_CB_COLOR5_INFO 240 
#define  R_0280B8_CB_COLOR6_INFO 239 
#define  R_0280BC_CB_COLOR7_INFO 238 
#define  R_0280C0_CB_COLOR0_TILE 237 
#define  R_0280C4_CB_COLOR1_TILE 236 
#define  R_0280C8_CB_COLOR2_TILE 235 
#define  R_0280CC_CB_COLOR3_TILE 234 
#define  R_0280D0_CB_COLOR4_TILE 233 
#define  R_0280D4_CB_COLOR5_TILE 232 
#define  R_0280D8_CB_COLOR6_TILE 231 
#define  R_0280DC_CB_COLOR7_TILE 230 
#define  R_0280E0_CB_COLOR0_FRAG 229 
#define  R_0280E4_CB_COLOR1_FRAG 228 
#define  R_0280E8_CB_COLOR2_FRAG 227 
#define  R_0280EC_CB_COLOR3_FRAG 226 
#define  R_0280F0_CB_COLOR4_FRAG 225 
#define  R_0280F4_CB_COLOR5_FRAG 224 
#define  R_0280F8_CB_COLOR6_FRAG 223 
#define  R_0280FC_CB_COLOR7_FRAG 222 
#define  R_028100_CB_COLOR0_MASK 221 
#define  R_028104_CB_COLOR1_MASK 220 
#define  R_028108_CB_COLOR2_MASK 219 
#define  R_02810C_CB_COLOR3_MASK 218 
#define  R_028110_CB_COLOR4_MASK 217 
#define  R_028114_CB_COLOR5_MASK 216 
#define  R_028118_CB_COLOR6_MASK 215 
#define  R_02811C_CB_COLOR7_MASK 214 
#define  R_028238_CB_TARGET_MASK 213 
#define  R_02823C_CB_SHADER_MASK 212 
#define  R_028800_DB_DEPTH_CONTROL 211 
#define  R_028808_CB_COLOR_CONTROL 210 
#define  R_0288A8_SQ_ESGS_RING_ITEMSIZE 209 
#define  R_0288AC_SQ_GSVS_RING_ITEMSIZE 208 
#define  R_0288B0_SQ_ESTMP_RING_ITEMSIZE 207 
#define  R_0288B4_SQ_GSTMP_RING_ITEMSIZE 206 
#define  R_0288B8_SQ_VSTMP_RING_ITEMSIZE 205 
#define  R_0288BC_SQ_PSTMP_RING_ITEMSIZE 204 
#define  R_0288C0_SQ_FBUF_RING_ITEMSIZE 203 
#define  R_0288C4_SQ_REDUC_RING_ITEMSIZE 202 
#define  R_0288C8_SQ_GS_VERT_ITEMSIZE 201 
#define  R_028AB0_VGT_STRMOUT_EN 200 
#define  R_028B20_VGT_STRMOUT_BUFFER_EN 199 
#define  R_028C04_PA_SC_AA_CONFIG 198 
#define  SQ_ALU_CONST_CACHE_GS_0 197 
#define  SQ_ALU_CONST_CACHE_GS_1 196 
#define  SQ_ALU_CONST_CACHE_GS_10 195 
#define  SQ_ALU_CONST_CACHE_GS_11 194 
#define  SQ_ALU_CONST_CACHE_GS_12 193 
#define  SQ_ALU_CONST_CACHE_GS_13 192 
#define  SQ_ALU_CONST_CACHE_GS_14 191 
#define  SQ_ALU_CONST_CACHE_GS_15 190 
#define  SQ_ALU_CONST_CACHE_GS_2 189 
#define  SQ_ALU_CONST_CACHE_GS_3 188 
#define  SQ_ALU_CONST_CACHE_GS_4 187 
#define  SQ_ALU_CONST_CACHE_GS_5 186 
#define  SQ_ALU_CONST_CACHE_GS_6 185 
#define  SQ_ALU_CONST_CACHE_GS_7 184 
#define  SQ_ALU_CONST_CACHE_GS_8 183 
#define  SQ_ALU_CONST_CACHE_GS_9 182 
#define  SQ_ALU_CONST_CACHE_PS_0 181 
#define  SQ_ALU_CONST_CACHE_PS_1 180 
#define  SQ_ALU_CONST_CACHE_PS_10 179 
#define  SQ_ALU_CONST_CACHE_PS_11 178 
#define  SQ_ALU_CONST_CACHE_PS_12 177 
#define  SQ_ALU_CONST_CACHE_PS_13 176 
#define  SQ_ALU_CONST_CACHE_PS_14 175 
#define  SQ_ALU_CONST_CACHE_PS_15 174 
#define  SQ_ALU_CONST_CACHE_PS_2 173 
#define  SQ_ALU_CONST_CACHE_PS_3 172 
#define  SQ_ALU_CONST_CACHE_PS_4 171 
#define  SQ_ALU_CONST_CACHE_PS_5 170 
#define  SQ_ALU_CONST_CACHE_PS_6 169 
#define  SQ_ALU_CONST_CACHE_PS_7 168 
#define  SQ_ALU_CONST_CACHE_PS_8 167 
#define  SQ_ALU_CONST_CACHE_PS_9 166 
#define  SQ_ALU_CONST_CACHE_VS_0 165 
#define  SQ_ALU_CONST_CACHE_VS_1 164 
#define  SQ_ALU_CONST_CACHE_VS_10 163 
#define  SQ_ALU_CONST_CACHE_VS_11 162 
#define  SQ_ALU_CONST_CACHE_VS_12 161 
#define  SQ_ALU_CONST_CACHE_VS_13 160 
#define  SQ_ALU_CONST_CACHE_VS_14 159 
#define  SQ_ALU_CONST_CACHE_VS_15 158 
#define  SQ_ALU_CONST_CACHE_VS_2 157 
#define  SQ_ALU_CONST_CACHE_VS_3 156 
#define  SQ_ALU_CONST_CACHE_VS_4 155 
#define  SQ_ALU_CONST_CACHE_VS_5 154 
#define  SQ_ALU_CONST_CACHE_VS_6 153 
#define  SQ_ALU_CONST_CACHE_VS_7 152 
#define  SQ_ALU_CONST_CACHE_VS_8 151 
#define  SQ_ALU_CONST_CACHE_VS_9 150 
#define  SQ_CONFIG 149 
#define  SQ_ESGS_RING_BASE 148 
#define  SQ_ESTMP_RING_BASE 147 
#define  SQ_GSTMP_RING_BASE 146 
#define  SQ_GSVS_RING_BASE 145 
#define  SQ_PGM_START_ES 144 
#define  SQ_PGM_START_FS 143 
#define  SQ_PGM_START_GS 142 
#define  SQ_PGM_START_PS 141 
#define  SQ_PGM_START_VS 140 
#define  SQ_PSTMP_RING_BASE 139 
#define  SQ_VSTMP_RING_BASE 138 
#define  SX_MEMORY_EXPORT_BASE 137 
#define  SX_MISC 136 
 int S_028010_ARRAY_MODE (int /*<<< orphan*/ ) ; 
 int S_0280A0_ARRAY_MODE (int /*<<< orphan*/ ) ; 
#define  VGT_STRMOUT_BUFFER_BASE_0 135 
#define  VGT_STRMOUT_BUFFER_BASE_1 134 
#define  VGT_STRMOUT_BUFFER_BASE_2 133 
#define  VGT_STRMOUT_BUFFER_BASE_3 132 
#define  VGT_STRMOUT_BUFFER_SIZE_0 131 
#define  VGT_STRMOUT_BUFFER_SIZE_1 130 
#define  VGT_STRMOUT_BUFFER_SIZE_2 129 
#define  VGT_STRMOUT_BUFFER_SIZE_3 128 
 int /*<<< orphan*/  V_028010_ARRAY_1D_TILED_THIN1 ; 
 int /*<<< orphan*/  V_028010_ARRAY_2D_TILED_THIN1 ; 
 int /*<<< orphan*/  V_0280A0_ARRAY_1D_TILED_THIN1 ; 
 int /*<<< orphan*/  V_0280A0_ARRAY_2D_TILED_THIN1 ; 
 int V_028808_SPECIAL_RESOLVE_BOX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  r600_nomm ; 
 int* r600_reg_safe_bm ; 
 int /*<<< orphan*/  radeon_cs_packet_next_is_pkt3_nop (struct radeon_cs_parser*) ; 
 int radeon_cs_packet_next_reloc (struct radeon_cs_parser*,struct radeon_bo_list**,int /*<<< orphan*/ ) ; 
 int radeon_get_ib_value (struct radeon_cs_parser*,int) ; 

__attribute__((used)) static int r600_cs_check_reg(struct radeon_cs_parser *p, u32 reg, u32 idx)
{
	struct r600_cs_track *track = (struct r600_cs_track *)p->track;
	struct radeon_bo_list *reloc;
	u32 m, i, tmp, *ib;
	int r;

	i = (reg >> 7);
	if (i >= ARRAY_SIZE(r600_reg_safe_bm)) {
		dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
		return -EINVAL;
	}
	m = 1 << ((reg >> 2) & 31);
	if (!(r600_reg_safe_bm[i] & m))
		return 0;
	ib = p->ib.ptr;
	switch (reg) {
	/* force following reg to 0 in an attempt to disable out buffer
	 * which will need us to better understand how it works to perform
	 * security check on it (Jerome)
	 */
	case R_0288A8_SQ_ESGS_RING_ITEMSIZE:
	case R_008C44_SQ_ESGS_RING_SIZE:
	case R_0288B0_SQ_ESTMP_RING_ITEMSIZE:
	case R_008C54_SQ_ESTMP_RING_SIZE:
	case R_0288C0_SQ_FBUF_RING_ITEMSIZE:
	case R_008C74_SQ_FBUF_RING_SIZE:
	case R_0288B4_SQ_GSTMP_RING_ITEMSIZE:
	case R_008C5C_SQ_GSTMP_RING_SIZE:
	case R_0288AC_SQ_GSVS_RING_ITEMSIZE:
	case R_008C4C_SQ_GSVS_RING_SIZE:
	case R_0288BC_SQ_PSTMP_RING_ITEMSIZE:
	case R_008C6C_SQ_PSTMP_RING_SIZE:
	case R_0288C4_SQ_REDUC_RING_ITEMSIZE:
	case R_008C7C_SQ_REDUC_RING_SIZE:
	case R_0288B8_SQ_VSTMP_RING_ITEMSIZE:
	case R_008C64_SQ_VSTMP_RING_SIZE:
	case R_0288C8_SQ_GS_VERT_ITEMSIZE:
		/* get value to populate the IB don't remove */
		/*tmp =radeon_get_ib_value(p, idx);
		  ib[idx] = 0;*/
		break;
	case SQ_ESGS_RING_BASE:
	case SQ_GSVS_RING_BASE:
	case SQ_ESTMP_RING_BASE:
	case SQ_GSTMP_RING_BASE:
	case SQ_PSTMP_RING_BASE:
	case SQ_VSTMP_RING_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			return -EINVAL;
		}
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		break;
	case SQ_CONFIG:
		track->sq_config = radeon_get_ib_value(p, idx);
		break;
	case R_028800_DB_DEPTH_CONTROL:
		track->db_depth_control = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		break;
	case R_028010_DB_DEPTH_INFO:
		if (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS) &&
		    radeon_cs_packet_next_is_pkt3_nop(p)) {
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			if (r) {
				dev_warn(p->dev, "bad SET_CONTEXT_REG "
					 "0x%04X\n", reg);
				return -EINVAL;
			}
			track->db_depth_info = radeon_get_ib_value(p, idx);
			ib[idx] &= C_028010_ARRAY_MODE;
			track->db_depth_info &= C_028010_ARRAY_MODE;
			if (reloc->tiling_flags & RADEON_TILING_MACRO) {
				ib[idx] |= S_028010_ARRAY_MODE(V_028010_ARRAY_2D_TILED_THIN1);
				track->db_depth_info |= S_028010_ARRAY_MODE(V_028010_ARRAY_2D_TILED_THIN1);
			} else {
				ib[idx] |= S_028010_ARRAY_MODE(V_028010_ARRAY_1D_TILED_THIN1);
				track->db_depth_info |= S_028010_ARRAY_MODE(V_028010_ARRAY_1D_TILED_THIN1);
			}
		} else {
			track->db_depth_info = radeon_get_ib_value(p, idx);
		}
		track->db_dirty = true;
		break;
	case R_028004_DB_DEPTH_VIEW:
		track->db_depth_view = radeon_get_ib_value(p, idx);
		track->db_dirty = true;
		break;
	case R_028000_DB_DEPTH_SIZE:
		track->db_depth_size = radeon_get_ib_value(p, idx);
		track->db_depth_size_idx = idx;
		track->db_dirty = true;
		break;
	case R_028AB0_VGT_STRMOUT_EN:
		track->vgt_strmout_en = radeon_get_ib_value(p, idx);
		track->streamout_dirty = true;
		break;
	case R_028B20_VGT_STRMOUT_BUFFER_EN:
		track->vgt_strmout_buffer_en = radeon_get_ib_value(p, idx);
		track->streamout_dirty = true;
		break;
	case VGT_STRMOUT_BUFFER_BASE_0:
	case VGT_STRMOUT_BUFFER_BASE_1:
	case VGT_STRMOUT_BUFFER_BASE_2:
	case VGT_STRMOUT_BUFFER_BASE_3:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		if (r) {
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			return -EINVAL;
		}
		tmp = (reg - VGT_STRMOUT_BUFFER_BASE_0) / 16;
		track->vgt_strmout_bo_offset[tmp] = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->vgt_strmout_bo[tmp] = reloc->robj;
		track->vgt_strmout_bo_mc[tmp] = reloc->gpu_offset;
		track->streamout_dirty = true;
		break;
	case VGT_STRMOUT_BUFFER_SIZE_0:
	case VGT_STRMOUT_BUFFER_SIZE_1:
	case VGT_STRMOUT_BUFFER_SIZE_2:
	case VGT_STRMOUT_BUFFER_SIZE_3:
		tmp = (reg - VGT_STRMOUT_BUFFER_SIZE_0) / 16;
		/* size in register is DWs, convert to bytes */
		track->vgt_strmout_size[tmp] = radeon_get_ib_value(p, idx) * 4;
		track->streamout_dirty = true;
		break;
	case CP_COHER_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		if (r) {
			dev_warn(p->dev, "missing reloc for CP_COHER_BASE "
					"0x%04X\n", reg);
			return -EINVAL;
		}
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		break;
	case R_028238_CB_TARGET_MASK:
		track->cb_target_mask = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		break;
	case R_02823C_CB_SHADER_MASK:
		track->cb_shader_mask = radeon_get_ib_value(p, idx);
		break;
	case R_028C04_PA_SC_AA_CONFIG:
		tmp = G_028C04_MSAA_NUM_SAMPLES(radeon_get_ib_value(p, idx));
		track->log_nsamples = tmp;
		track->nsamples = 1 << tmp;
		track->cb_dirty = true;
		break;
	case R_028808_CB_COLOR_CONTROL:
		tmp = G_028808_SPECIAL_OP(radeon_get_ib_value(p, idx));
		track->is_resolve = tmp == V_028808_SPECIAL_RESOLVE_BOX;
		track->cb_dirty = true;
		break;
	case R_0280A0_CB_COLOR0_INFO:
	case R_0280A4_CB_COLOR1_INFO:
	case R_0280A8_CB_COLOR2_INFO:
	case R_0280AC_CB_COLOR3_INFO:
	case R_0280B0_CB_COLOR4_INFO:
	case R_0280B4_CB_COLOR5_INFO:
	case R_0280B8_CB_COLOR6_INFO:
	case R_0280BC_CB_COLOR7_INFO:
		if (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS) &&
		     radeon_cs_packet_next_is_pkt3_nop(p)) {
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			if (r) {
				dev_err(p->dev, "bad SET_CONTEXT_REG 0x%04X\n", reg);
				return -EINVAL;
			}
			tmp = (reg - R_0280A0_CB_COLOR0_INFO) / 4;
			track->cb_color_info[tmp] = radeon_get_ib_value(p, idx);
			if (reloc->tiling_flags & RADEON_TILING_MACRO) {
				ib[idx] |= S_0280A0_ARRAY_MODE(V_0280A0_ARRAY_2D_TILED_THIN1);
				track->cb_color_info[tmp] |= S_0280A0_ARRAY_MODE(V_0280A0_ARRAY_2D_TILED_THIN1);
			} else if (reloc->tiling_flags & RADEON_TILING_MICRO) {
				ib[idx] |= S_0280A0_ARRAY_MODE(V_0280A0_ARRAY_1D_TILED_THIN1);
				track->cb_color_info[tmp] |= S_0280A0_ARRAY_MODE(V_0280A0_ARRAY_1D_TILED_THIN1);
			}
		} else {
			tmp = (reg - R_0280A0_CB_COLOR0_INFO) / 4;
			track->cb_color_info[tmp] = radeon_get_ib_value(p, idx);
		}
		track->cb_dirty = true;
		break;
	case R_028080_CB_COLOR0_VIEW:
	case R_028084_CB_COLOR1_VIEW:
	case R_028088_CB_COLOR2_VIEW:
	case R_02808C_CB_COLOR3_VIEW:
	case R_028090_CB_COLOR4_VIEW:
	case R_028094_CB_COLOR5_VIEW:
	case R_028098_CB_COLOR6_VIEW:
	case R_02809C_CB_COLOR7_VIEW:
		tmp = (reg - R_028080_CB_COLOR0_VIEW) / 4;
		track->cb_color_view[tmp] = radeon_get_ib_value(p, idx);
		track->cb_dirty = true;
		break;
	case R_028060_CB_COLOR0_SIZE:
	case R_028064_CB_COLOR1_SIZE:
	case R_028068_CB_COLOR2_SIZE:
	case R_02806C_CB_COLOR3_SIZE:
	case R_028070_CB_COLOR4_SIZE:
	case R_028074_CB_COLOR5_SIZE:
	case R_028078_CB_COLOR6_SIZE:
	case R_02807C_CB_COLOR7_SIZE:
		tmp = (reg - R_028060_CB_COLOR0_SIZE) / 4;
		track->cb_color_size[tmp] = radeon_get_ib_value(p, idx);
		track->cb_color_size_idx[tmp] = idx;
		track->cb_dirty = true;
		break;
		/* This register were added late, there is userspace
		 * which does provide relocation for those but set
		 * 0 offset. In order to avoid breaking old userspace
		 * we detect this and set address to point to last
		 * CB_COLOR0_BASE, note that if userspace doesn't set
		 * CB_COLOR0_BASE before this register we will report
		 * error. Old userspace always set CB_COLOR0_BASE
		 * before any of this.
		 */
	case R_0280E0_CB_COLOR0_FRAG:
	case R_0280E4_CB_COLOR1_FRAG:
	case R_0280E8_CB_COLOR2_FRAG:
	case R_0280EC_CB_COLOR3_FRAG:
	case R_0280F0_CB_COLOR4_FRAG:
	case R_0280F4_CB_COLOR5_FRAG:
	case R_0280F8_CB_COLOR6_FRAG:
	case R_0280FC_CB_COLOR7_FRAG:
		tmp = (reg - R_0280E0_CB_COLOR0_FRAG) / 4;
		if (!radeon_cs_packet_next_is_pkt3_nop(p)) {
			if (!track->cb_color_base_last[tmp]) {
				dev_err(p->dev, "Broken old userspace ? no cb_color0_base supplied before trying to write 0x%08X\n", reg);
				return -EINVAL;
			}
			track->cb_color_frag_bo[tmp] = track->cb_color_bo[tmp];
			track->cb_color_frag_offset[tmp] = track->cb_color_bo_offset[tmp];
			ib[idx] = track->cb_color_base_last[tmp];
		} else {
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			if (r) {
				dev_err(p->dev, "bad SET_CONTEXT_REG 0x%04X\n", reg);
				return -EINVAL;
			}
			track->cb_color_frag_bo[tmp] = reloc->robj;
			track->cb_color_frag_offset[tmp] = (u64)ib[idx] << 8;
			ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		}
		if (G_0280A0_TILE_MODE(track->cb_color_info[tmp])) {
			track->cb_dirty = true;
		}
		break;
	case R_0280C0_CB_COLOR0_TILE:
	case R_0280C4_CB_COLOR1_TILE:
	case R_0280C8_CB_COLOR2_TILE:
	case R_0280CC_CB_COLOR3_TILE:
	case R_0280D0_CB_COLOR4_TILE:
	case R_0280D4_CB_COLOR5_TILE:
	case R_0280D8_CB_COLOR6_TILE:
	case R_0280DC_CB_COLOR7_TILE:
		tmp = (reg - R_0280C0_CB_COLOR0_TILE) / 4;
		if (!radeon_cs_packet_next_is_pkt3_nop(p)) {
			if (!track->cb_color_base_last[tmp]) {
				dev_err(p->dev, "Broken old userspace ? no cb_color0_base supplied before trying to write 0x%08X\n", reg);
				return -EINVAL;
			}
			track->cb_color_tile_bo[tmp] = track->cb_color_bo[tmp];
			track->cb_color_tile_offset[tmp] = track->cb_color_bo_offset[tmp];
			ib[idx] = track->cb_color_base_last[tmp];
		} else {
			r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
			if (r) {
				dev_err(p->dev, "bad SET_CONTEXT_REG 0x%04X\n", reg);
				return -EINVAL;
			}
			track->cb_color_tile_bo[tmp] = reloc->robj;
			track->cb_color_tile_offset[tmp] = (u64)ib[idx] << 8;
			ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		}
		if (G_0280A0_TILE_MODE(track->cb_color_info[tmp])) {
			track->cb_dirty = true;
		}
		break;
	case R_028100_CB_COLOR0_MASK:
	case R_028104_CB_COLOR1_MASK:
	case R_028108_CB_COLOR2_MASK:
	case R_02810C_CB_COLOR3_MASK:
	case R_028110_CB_COLOR4_MASK:
	case R_028114_CB_COLOR5_MASK:
	case R_028118_CB_COLOR6_MASK:
	case R_02811C_CB_COLOR7_MASK:
		tmp = (reg - R_028100_CB_COLOR0_MASK) / 4;
		track->cb_color_mask[tmp] = radeon_get_ib_value(p, idx);
		if (G_0280A0_TILE_MODE(track->cb_color_info[tmp])) {
			track->cb_dirty = true;
		}
		break;
	case CB_COLOR0_BASE:
	case CB_COLOR1_BASE:
	case CB_COLOR2_BASE:
	case CB_COLOR3_BASE:
	case CB_COLOR4_BASE:
	case CB_COLOR5_BASE:
	case CB_COLOR6_BASE:
	case CB_COLOR7_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		if (r) {
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			return -EINVAL;
		}
		tmp = (reg - CB_COLOR0_BASE) / 4;
		track->cb_color_bo_offset[tmp] = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->cb_color_base_last[tmp] = ib[idx];
		track->cb_color_bo[tmp] = reloc->robj;
		track->cb_color_bo_mc[tmp] = reloc->gpu_offset;
		track->cb_dirty = true;
		break;
	case DB_DEPTH_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		if (r) {
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			return -EINVAL;
		}
		track->db_offset = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->db_bo = reloc->robj;
		track->db_bo_mc = reloc->gpu_offset;
		track->db_dirty = true;
		break;
	case DB_HTILE_DATA_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		if (r) {
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			return -EINVAL;
		}
		track->htile_offset = radeon_get_ib_value(p, idx) << 8;
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		track->htile_bo = reloc->robj;
		track->db_dirty = true;
		break;
	case DB_HTILE_SURFACE:
		track->htile_surface = radeon_get_ib_value(p, idx);
		/* force 8x8 htile width and height */
		ib[idx] |= 3;
		track->db_dirty = true;
		break;
	case SQ_PGM_START_FS:
	case SQ_PGM_START_ES:
	case SQ_PGM_START_VS:
	case SQ_PGM_START_GS:
	case SQ_PGM_START_PS:
	case SQ_ALU_CONST_CACHE_GS_0:
	case SQ_ALU_CONST_CACHE_GS_1:
	case SQ_ALU_CONST_CACHE_GS_2:
	case SQ_ALU_CONST_CACHE_GS_3:
	case SQ_ALU_CONST_CACHE_GS_4:
	case SQ_ALU_CONST_CACHE_GS_5:
	case SQ_ALU_CONST_CACHE_GS_6:
	case SQ_ALU_CONST_CACHE_GS_7:
	case SQ_ALU_CONST_CACHE_GS_8:
	case SQ_ALU_CONST_CACHE_GS_9:
	case SQ_ALU_CONST_CACHE_GS_10:
	case SQ_ALU_CONST_CACHE_GS_11:
	case SQ_ALU_CONST_CACHE_GS_12:
	case SQ_ALU_CONST_CACHE_GS_13:
	case SQ_ALU_CONST_CACHE_GS_14:
	case SQ_ALU_CONST_CACHE_GS_15:
	case SQ_ALU_CONST_CACHE_PS_0:
	case SQ_ALU_CONST_CACHE_PS_1:
	case SQ_ALU_CONST_CACHE_PS_2:
	case SQ_ALU_CONST_CACHE_PS_3:
	case SQ_ALU_CONST_CACHE_PS_4:
	case SQ_ALU_CONST_CACHE_PS_5:
	case SQ_ALU_CONST_CACHE_PS_6:
	case SQ_ALU_CONST_CACHE_PS_7:
	case SQ_ALU_CONST_CACHE_PS_8:
	case SQ_ALU_CONST_CACHE_PS_9:
	case SQ_ALU_CONST_CACHE_PS_10:
	case SQ_ALU_CONST_CACHE_PS_11:
	case SQ_ALU_CONST_CACHE_PS_12:
	case SQ_ALU_CONST_CACHE_PS_13:
	case SQ_ALU_CONST_CACHE_PS_14:
	case SQ_ALU_CONST_CACHE_PS_15:
	case SQ_ALU_CONST_CACHE_VS_0:
	case SQ_ALU_CONST_CACHE_VS_1:
	case SQ_ALU_CONST_CACHE_VS_2:
	case SQ_ALU_CONST_CACHE_VS_3:
	case SQ_ALU_CONST_CACHE_VS_4:
	case SQ_ALU_CONST_CACHE_VS_5:
	case SQ_ALU_CONST_CACHE_VS_6:
	case SQ_ALU_CONST_CACHE_VS_7:
	case SQ_ALU_CONST_CACHE_VS_8:
	case SQ_ALU_CONST_CACHE_VS_9:
	case SQ_ALU_CONST_CACHE_VS_10:
	case SQ_ALU_CONST_CACHE_VS_11:
	case SQ_ALU_CONST_CACHE_VS_12:
	case SQ_ALU_CONST_CACHE_VS_13:
	case SQ_ALU_CONST_CACHE_VS_14:
	case SQ_ALU_CONST_CACHE_VS_15:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		if (r) {
			dev_warn(p->dev, "bad SET_CONTEXT_REG "
					"0x%04X\n", reg);
			return -EINVAL;
		}
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		break;
	case SX_MEMORY_EXPORT_BASE:
		r = radeon_cs_packet_next_reloc(p, &reloc, r600_nomm);
		if (r) {
			dev_warn(p->dev, "bad SET_CONFIG_REG "
					"0x%04X\n", reg);
			return -EINVAL;
		}
		ib[idx] += (u32)((reloc->gpu_offset >> 8) & 0xffffffff);
		break;
	case SX_MISC:
		track->sx_misc_kill_all_prims = (radeon_get_ib_value(p, idx) & 0x1) != 0;
		break;
	default:
		dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
		return -EINVAL;
	}
	return 0;
}