#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_framebuffer {int* pitches; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_9__* format; } ;
struct drm_format_name_buf {int dummy; } ;
struct TYPE_27__ {scalar_t__ v_taps; scalar_t__ h_taps; scalar_t__ v_taps_c; scalar_t__ h_taps_c; } ;
struct TYPE_26__ {int shaderEnable; void* swizzle; int /*<<< orphan*/  num_rb_per_se; int /*<<< orphan*/  max_compressed_frags; int /*<<< orphan*/  num_shader_engines; int /*<<< orphan*/  pipe_interleave; int /*<<< orphan*/  num_banks; int /*<<< orphan*/  num_pipes; } ;
struct TYPE_22__ {unsigned int num_banks; unsigned int tile_split; unsigned int bank_width; unsigned int bank_height; unsigned int tile_aspect; void* pipe_config; void* array_mode; int /*<<< orphan*/  tile_mode; } ;
struct TYPE_21__ {TYPE_5__ gfx9; TYPE_1__ gfx8; } ;
struct TYPE_19__ {unsigned int width; int /*<<< orphan*/  height; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_17__ {unsigned int width; int /*<<< orphan*/  height; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_20__ {unsigned int luma_pitch; unsigned int chroma_pitch; TYPE_13__ chroma_size; TYPE_11__ luma_size; } ;
struct TYPE_28__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_29__ {int surface_pitch; TYPE_7__ surface_size; } ;
struct TYPE_18__ {TYPE_14__ video; TYPE_8__ grph; } ;
struct TYPE_16__ {int /*<<< orphan*/  type; } ;
struct dc_plane_state {scalar_t__ format; int visible; int /*<<< orphan*/  stereo_format; TYPE_6__ scaling_quality; TYPE_15__ tiling_info; int /*<<< orphan*/  color_space; TYPE_12__ plane_size; TYPE_10__ address; } ;
struct amdgpu_framebuffer {struct drm_framebuffer base; } ;
struct TYPE_23__ {int /*<<< orphan*/  num_rb_per_se; int /*<<< orphan*/  max_compress_frags; int /*<<< orphan*/  num_se; int /*<<< orphan*/  pipe_interleave_size; int /*<<< orphan*/  num_banks; int /*<<< orphan*/  num_pipes; } ;
struct TYPE_24__ {TYPE_2__ gb_addr_config_fields; } ;
struct TYPE_25__ {TYPE_3__ config; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_4__ gfx; } ;
struct TYPE_30__ {int format; int* cpp; } ;

/* Variables and functions */
 unsigned int ALIGN (int /*<<< orphan*/ ,int) ; 
 void* AMDGPU_TILING_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_MODE ; 
 int /*<<< orphan*/  BANK_HEIGHT ; 
 int /*<<< orphan*/  BANK_WIDTH ; 
 scalar_t__ CHIP_RAVEN ; 
 scalar_t__ CHIP_VEGA10 ; 
 scalar_t__ CHIP_VEGA12 ; 
 scalar_t__ CHIP_VEGA20 ; 
 int /*<<< orphan*/  COLOR_SPACE_SRGB ; 
 int /*<<< orphan*/  COLOR_SPACE_YCBCR709 ; 
 int /*<<< orphan*/  DC_ADDR_SURF_MICRO_TILING_DISPLAY ; 
 void* DC_ARRAY_1D_TILED_THIN1 ; 
 void* DC_ARRAY_2D_TILED_THIN1 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
#define  DRM_FORMAT_ABGR2101010 137 
#define  DRM_FORMAT_ARGB2101010 136 
#define  DRM_FORMAT_ARGB8888 135 
#define  DRM_FORMAT_C8 134 
#define  DRM_FORMAT_NV12 133 
#define  DRM_FORMAT_NV21 132 
#define  DRM_FORMAT_RGB565 131 
#define  DRM_FORMAT_XBGR2101010 130 
#define  DRM_FORMAT_XRGB2101010 129 
#define  DRM_FORMAT_XRGB8888 128 
 int EINVAL ; 
 int /*<<< orphan*/  MACRO_TILE_ASPECT ; 
 int /*<<< orphan*/  NUM_BANKS ; 
 int /*<<< orphan*/  PIPE_CONFIG ; 
 int /*<<< orphan*/  PLANE_STEREO_FORMAT_NONE ; 
 int /*<<< orphan*/  PLN_ADDR_TYPE_GRAPHICS ; 
 int /*<<< orphan*/  PLN_ADDR_TYPE_VIDEO_PROGRESSIVE ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_GRPH_RGB565 ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 
 int /*<<< orphan*/  SWIZZLE_MODE ; 
 int /*<<< orphan*/  TILE_SPLIT ; 
 int /*<<< orphan*/  drm_get_format_name (int,struct drm_format_name_buf*) ; 
 int get_fb_info (struct amdgpu_framebuffer const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_15__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fill_plane_attributes_from_fb(struct amdgpu_device *adev,
					 struct dc_plane_state *plane_state,
					 const struct amdgpu_framebuffer *amdgpu_fb)
{
	uint64_t tiling_flags;
	unsigned int awidth;
	const struct drm_framebuffer *fb = &amdgpu_fb->base;
	int ret = 0;
	struct drm_format_name_buf format_name;

	ret = get_fb_info(
		amdgpu_fb,
		&tiling_flags);

	if (ret)
		return ret;

	switch (fb->format->format) {
	case DRM_FORMAT_C8:
		plane_state->format = SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS;
		break;
	case DRM_FORMAT_RGB565:
		plane_state->format = SURFACE_PIXEL_FORMAT_GRPH_RGB565;
		break;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		plane_state->format = SURFACE_PIXEL_FORMAT_GRPH_ARGB8888;
		break;
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_ARGB2101010:
		plane_state->format = SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010;
		break;
	case DRM_FORMAT_XBGR2101010:
	case DRM_FORMAT_ABGR2101010:
		plane_state->format = SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010;
		break;
	case DRM_FORMAT_NV21:
		plane_state->format = SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr;
		break;
	case DRM_FORMAT_NV12:
		plane_state->format = SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb;
		break;
	default:
		DRM_ERROR("Unsupported screen format %s\n",
			  drm_get_format_name(fb->format->format, &format_name));
		return -EINVAL;
	}

	if (plane_state->format < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) {
		plane_state->address.type = PLN_ADDR_TYPE_GRAPHICS;
		plane_state->plane_size.grph.surface_size.x = 0;
		plane_state->plane_size.grph.surface_size.y = 0;
		plane_state->plane_size.grph.surface_size.width = fb->width;
		plane_state->plane_size.grph.surface_size.height = fb->height;
		plane_state->plane_size.grph.surface_pitch =
				fb->pitches[0] / fb->format->cpp[0];
		/* TODO: unhardcode */
		plane_state->color_space = COLOR_SPACE_SRGB;

	} else {
		awidth = ALIGN(fb->width, 64);
		plane_state->address.type = PLN_ADDR_TYPE_VIDEO_PROGRESSIVE;
		plane_state->plane_size.video.luma_size.x = 0;
		plane_state->plane_size.video.luma_size.y = 0;
		plane_state->plane_size.video.luma_size.width = awidth;
		plane_state->plane_size.video.luma_size.height = fb->height;
		/* TODO: unhardcode */
		plane_state->plane_size.video.luma_pitch = awidth;

		plane_state->plane_size.video.chroma_size.x = 0;
		plane_state->plane_size.video.chroma_size.y = 0;
		plane_state->plane_size.video.chroma_size.width = awidth;
		plane_state->plane_size.video.chroma_size.height = fb->height;
		plane_state->plane_size.video.chroma_pitch = awidth / 2;

		/* TODO: unhardcode */
		plane_state->color_space = COLOR_SPACE_YCBCR709;
	}

	memset(&plane_state->tiling_info, 0, sizeof(plane_state->tiling_info));

	/* Fill GFX8 params */
	if (AMDGPU_TILING_GET(tiling_flags, ARRAY_MODE) == DC_ARRAY_2D_TILED_THIN1) {
		unsigned int bankw, bankh, mtaspect, tile_split, num_banks;

		bankw = AMDGPU_TILING_GET(tiling_flags, BANK_WIDTH);
		bankh = AMDGPU_TILING_GET(tiling_flags, BANK_HEIGHT);
		mtaspect = AMDGPU_TILING_GET(tiling_flags, MACRO_TILE_ASPECT);
		tile_split = AMDGPU_TILING_GET(tiling_flags, TILE_SPLIT);
		num_banks = AMDGPU_TILING_GET(tiling_flags, NUM_BANKS);

		/* XXX fix me for VI */
		plane_state->tiling_info.gfx8.num_banks = num_banks;
		plane_state->tiling_info.gfx8.array_mode =
				DC_ARRAY_2D_TILED_THIN1;
		plane_state->tiling_info.gfx8.tile_split = tile_split;
		plane_state->tiling_info.gfx8.bank_width = bankw;
		plane_state->tiling_info.gfx8.bank_height = bankh;
		plane_state->tiling_info.gfx8.tile_aspect = mtaspect;
		plane_state->tiling_info.gfx8.tile_mode =
				DC_ADDR_SURF_MICRO_TILING_DISPLAY;
	} else if (AMDGPU_TILING_GET(tiling_flags, ARRAY_MODE)
			== DC_ARRAY_1D_TILED_THIN1) {
		plane_state->tiling_info.gfx8.array_mode = DC_ARRAY_1D_TILED_THIN1;
	}

	plane_state->tiling_info.gfx8.pipe_config =
			AMDGPU_TILING_GET(tiling_flags, PIPE_CONFIG);

	if (adev->asic_type == CHIP_VEGA10 ||
	    adev->asic_type == CHIP_VEGA12 ||
	    adev->asic_type == CHIP_VEGA20 ||
	    adev->asic_type == CHIP_RAVEN) {
		/* Fill GFX9 params */
		plane_state->tiling_info.gfx9.num_pipes =
			adev->gfx.config.gb_addr_config_fields.num_pipes;
		plane_state->tiling_info.gfx9.num_banks =
			adev->gfx.config.gb_addr_config_fields.num_banks;
		plane_state->tiling_info.gfx9.pipe_interleave =
			adev->gfx.config.gb_addr_config_fields.pipe_interleave_size;
		plane_state->tiling_info.gfx9.num_shader_engines =
			adev->gfx.config.gb_addr_config_fields.num_se;
		plane_state->tiling_info.gfx9.max_compressed_frags =
			adev->gfx.config.gb_addr_config_fields.max_compress_frags;
		plane_state->tiling_info.gfx9.num_rb_per_se =
			adev->gfx.config.gb_addr_config_fields.num_rb_per_se;
		plane_state->tiling_info.gfx9.swizzle =
			AMDGPU_TILING_GET(tiling_flags, SWIZZLE_MODE);
		plane_state->tiling_info.gfx9.shaderEnable = 1;
	}

	plane_state->visible = true;
	plane_state->scaling_quality.h_taps_c = 0;
	plane_state->scaling_quality.v_taps_c = 0;

	/* is this needed? is plane_state zeroed at allocation? */
	plane_state->scaling_quality.h_taps = 0;
	plane_state->scaling_quality.v_taps = 0;
	plane_state->stereo_format = PLANE_STEREO_FORMAT_NONE;

	return ret;

}