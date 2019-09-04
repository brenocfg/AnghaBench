#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vc4_texture_sample_info {int* p_offset; scalar_t__ is_direct; } ;
struct vc4_exec_info {int* uniforms_v; int bin_dep_seqno; } ;
struct TYPE_4__ {int size; } ;
struct drm_gem_cma_object {int paddr; TYPE_2__ base; } ;
typedef  enum vc4_texture_data_type { ____Placeholder_vc4_texture_data_type } vc4_texture_data_type ;
struct TYPE_3__ {unsigned int write_seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int,int) ; 
 int VC4_GET_FIELD (int,int /*<<< orphan*/ ) ; 
#define  VC4_TEXTURE_TYPE_A1 147 
#define  VC4_TEXTURE_TYPE_A4 146 
#define  VC4_TEXTURE_TYPE_ALPHA 145 
#define  VC4_TEXTURE_TYPE_BW1 144 
#define  VC4_TEXTURE_TYPE_ETC1 143 
#define  VC4_TEXTURE_TYPE_LUMALPHA 142 
#define  VC4_TEXTURE_TYPE_LUMINANCE 141 
#define  VC4_TEXTURE_TYPE_RGB565 140 
#define  VC4_TEXTURE_TYPE_RGBA32R 139 
#define  VC4_TEXTURE_TYPE_RGBA4444 138 
#define  VC4_TEXTURE_TYPE_RGBA5551 137 
#define  VC4_TEXTURE_TYPE_RGBA64 136 
#define  VC4_TEXTURE_TYPE_RGBA8888 135 
#define  VC4_TEXTURE_TYPE_RGBX8888 134 
#define  VC4_TEXTURE_TYPE_S16 133 
#define  VC4_TEXTURE_TYPE_S16F 132 
#define  VC4_TEXTURE_TYPE_S8 131 
#define  VC4_TEXTURE_TYPE_YUV422R 130 
 int VC4_TEX_P0_CMMODE_MASK ; 
 int /*<<< orphan*/  VC4_TEX_P0_MIPLVLS ; 
 int VC4_TEX_P0_OFFSET_MASK ; 
 int /*<<< orphan*/  VC4_TEX_P0_TYPE ; 
 int /*<<< orphan*/  VC4_TEX_P1_HEIGHT ; 
 int /*<<< orphan*/  VC4_TEX_P1_TYPE4 ; 
 int /*<<< orphan*/  VC4_TEX_P1_WIDTH ; 
 int VC4_TEX_P2_CMST_MASK ; 
 int /*<<< orphan*/  VC4_TEX_P2_PTYPE ; 
 int VC4_TEX_P2_PTYPE_CUBE_MAP_STRIDE ; 
 int VC4_TILING_FORMAT_LINEAR ; 
#define  VC4_TILING_FORMAT_LT 129 
#define  VC4_TILING_FORMAT_T 128 
 void* max (int,unsigned int) ; 
 int round_up (int,int) ; 
 scalar_t__ size_is_lt (int,int,int) ; 
 TYPE_1__* to_vc4_bo (TYPE_2__*) ; 
 int utile_height (int) ; 
 int utile_width (int) ; 
 int /*<<< orphan*/  vc4_check_tex_size (struct vc4_exec_info*,struct drm_gem_cma_object*,int,int,int,int,int) ; 
 struct drm_gem_cma_object* vc4_use_bo (struct vc4_exec_info*,int) ; 

__attribute__((used)) static bool
reloc_tex(struct vc4_exec_info *exec,
	  void *uniform_data_u,
	  struct vc4_texture_sample_info *sample,
	  uint32_t texture_handle_index, bool is_cs)
{
	struct drm_gem_cma_object *tex;
	uint32_t p0 = *(uint32_t *)(uniform_data_u + sample->p_offset[0]);
	uint32_t p1 = *(uint32_t *)(uniform_data_u + sample->p_offset[1]);
	uint32_t p2 = (sample->p_offset[2] != ~0 ?
		       *(uint32_t *)(uniform_data_u + sample->p_offset[2]) : 0);
	uint32_t p3 = (sample->p_offset[3] != ~0 ?
		       *(uint32_t *)(uniform_data_u + sample->p_offset[3]) : 0);
	uint32_t *validated_p0 = exec->uniforms_v + sample->p_offset[0];
	uint32_t offset = p0 & VC4_TEX_P0_OFFSET_MASK;
	uint32_t miplevels = VC4_GET_FIELD(p0, VC4_TEX_P0_MIPLVLS);
	uint32_t width = VC4_GET_FIELD(p1, VC4_TEX_P1_WIDTH);
	uint32_t height = VC4_GET_FIELD(p1, VC4_TEX_P1_HEIGHT);
	uint32_t cpp, tiling_format, utile_w, utile_h;
	uint32_t i;
	uint32_t cube_map_stride = 0;
	enum vc4_texture_data_type type;

	tex = vc4_use_bo(exec, texture_handle_index);
	if (!tex)
		return false;

	if (sample->is_direct) {
		uint32_t remaining_size = tex->base.size - p0;

		if (p0 > tex->base.size - 4) {
			DRM_DEBUG("UBO offset greater than UBO size\n");
			goto fail;
		}
		if (p1 > remaining_size - 4) {
			DRM_DEBUG("UBO clamp would allow reads "
				  "outside of UBO\n");
			goto fail;
		}
		*validated_p0 = tex->paddr + p0;
		return true;
	}

	if (width == 0)
		width = 2048;
	if (height == 0)
		height = 2048;

	if (p0 & VC4_TEX_P0_CMMODE_MASK) {
		if (VC4_GET_FIELD(p2, VC4_TEX_P2_PTYPE) ==
		    VC4_TEX_P2_PTYPE_CUBE_MAP_STRIDE)
			cube_map_stride = p2 & VC4_TEX_P2_CMST_MASK;
		if (VC4_GET_FIELD(p3, VC4_TEX_P2_PTYPE) ==
		    VC4_TEX_P2_PTYPE_CUBE_MAP_STRIDE) {
			if (cube_map_stride) {
				DRM_DEBUG("Cube map stride set twice\n");
				goto fail;
			}

			cube_map_stride = p3 & VC4_TEX_P2_CMST_MASK;
		}
		if (!cube_map_stride) {
			DRM_DEBUG("Cube map stride not set\n");
			goto fail;
		}
	}

	type = (VC4_GET_FIELD(p0, VC4_TEX_P0_TYPE) |
		(VC4_GET_FIELD(p1, VC4_TEX_P1_TYPE4) << 4));

	switch (type) {
	case VC4_TEXTURE_TYPE_RGBA8888:
	case VC4_TEXTURE_TYPE_RGBX8888:
	case VC4_TEXTURE_TYPE_RGBA32R:
		cpp = 4;
		break;
	case VC4_TEXTURE_TYPE_RGBA4444:
	case VC4_TEXTURE_TYPE_RGBA5551:
	case VC4_TEXTURE_TYPE_RGB565:
	case VC4_TEXTURE_TYPE_LUMALPHA:
	case VC4_TEXTURE_TYPE_S16F:
	case VC4_TEXTURE_TYPE_S16:
		cpp = 2;
		break;
	case VC4_TEXTURE_TYPE_LUMINANCE:
	case VC4_TEXTURE_TYPE_ALPHA:
	case VC4_TEXTURE_TYPE_S8:
		cpp = 1;
		break;
	case VC4_TEXTURE_TYPE_ETC1:
		/* ETC1 is arranged as 64-bit blocks, where each block is 4x4
		 * pixels.
		 */
		cpp = 8;
		width = (width + 3) >> 2;
		height = (height + 3) >> 2;
		break;
	case VC4_TEXTURE_TYPE_BW1:
	case VC4_TEXTURE_TYPE_A4:
	case VC4_TEXTURE_TYPE_A1:
	case VC4_TEXTURE_TYPE_RGBA64:
	case VC4_TEXTURE_TYPE_YUV422R:
	default:
		DRM_DEBUG("Texture format %d unsupported\n", type);
		goto fail;
	}
	utile_w = utile_width(cpp);
	utile_h = utile_height(cpp);

	if (type == VC4_TEXTURE_TYPE_RGBA32R) {
		tiling_format = VC4_TILING_FORMAT_LINEAR;
	} else {
		if (size_is_lt(width, height, cpp))
			tiling_format = VC4_TILING_FORMAT_LT;
		else
			tiling_format = VC4_TILING_FORMAT_T;
	}

	if (!vc4_check_tex_size(exec, tex, offset + cube_map_stride * 5,
				tiling_format, width, height, cpp)) {
		goto fail;
	}

	/* The mipmap levels are stored before the base of the texture.  Make
	 * sure there is actually space in the BO.
	 */
	for (i = 1; i <= miplevels; i++) {
		uint32_t level_width = max(width >> i, 1u);
		uint32_t level_height = max(height >> i, 1u);
		uint32_t aligned_width, aligned_height;
		uint32_t level_size;

		/* Once the levels get small enough, they drop from T to LT. */
		if (tiling_format == VC4_TILING_FORMAT_T &&
		    size_is_lt(level_width, level_height, cpp)) {
			tiling_format = VC4_TILING_FORMAT_LT;
		}

		switch (tiling_format) {
		case VC4_TILING_FORMAT_T:
			aligned_width = round_up(level_width, utile_w * 8);
			aligned_height = round_up(level_height, utile_h * 8);
			break;
		case VC4_TILING_FORMAT_LT:
			aligned_width = round_up(level_width, utile_w);
			aligned_height = round_up(level_height, utile_h);
			break;
		default:
			aligned_width = round_up(level_width, utile_w);
			aligned_height = level_height;
			break;
		}

		level_size = aligned_width * cpp * aligned_height;

		if (offset < level_size) {
			DRM_DEBUG("Level %d (%dx%d -> %dx%d) size %db "
				  "overflowed buffer bounds (offset %d)\n",
				  i, level_width, level_height,
				  aligned_width, aligned_height,
				  level_size, offset);
			goto fail;
		}

		offset -= level_size;
	}

	*validated_p0 = tex->paddr + p0;

	if (is_cs) {
		exec->bin_dep_seqno = max(exec->bin_dep_seqno,
					  to_vc4_bo(&tex->base)->write_seqno);
	}

	return true;
 fail:
	DRM_INFO("Texture p0 at %d: 0x%08x\n", sample->p_offset[0], p0);
	DRM_INFO("Texture p1 at %d: 0x%08x\n", sample->p_offset[1], p1);
	DRM_INFO("Texture p2 at %d: 0x%08x\n", sample->p_offset[2], p2);
	DRM_INFO("Texture p3 at %d: 0x%08x\n", sample->p_offset[3], p3);
	return false;
}