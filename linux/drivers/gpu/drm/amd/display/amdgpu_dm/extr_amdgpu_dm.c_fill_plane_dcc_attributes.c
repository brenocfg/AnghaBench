#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  swizzle; } ;
union dc_tiling_info {TYPE_4__ gfx9; } ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct plane_size {TYPE_3__ surface_size; } ;
struct TYPE_15__ {scalar_t__ independent_64b_blks; } ;
struct TYPE_16__ {TYPE_6__ rgb; } ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct dc_surface_dcc_cap {int format; TYPE_7__ grph; int /*<<< orphan*/  capable; int /*<<< orphan*/  scan; int /*<<< orphan*/  swizzle_mode; TYPE_2__ surface_size; } ;
struct dc_plane_dcc_param {int enable; scalar_t__ independent_64b_blks; scalar_t__ meta_pitch; } ;
struct TYPE_17__ {int /*<<< orphan*/  high_part; int /*<<< orphan*/  low_part; } ;
struct TYPE_18__ {TYPE_8__ meta_addr; } ;
struct dc_plane_address {TYPE_9__ grph; } ;
struct dc_dcc_surface_param {int format; TYPE_7__ grph; int /*<<< orphan*/  capable; int /*<<< orphan*/  scan; int /*<<< orphan*/  swizzle_mode; TYPE_2__ surface_size; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* get_dcc_compression_cap ) (struct dc*,struct dc_surface_dcc_cap*,struct dc_surface_dcc_cap*) ;} ;
struct dc {TYPE_5__ cap_funcs; } ;
struct amdgpu_framebuffer {int /*<<< orphan*/  address; } ;
struct TYPE_10__ {struct dc* dc; } ;
struct amdgpu_device {TYPE_1__ dm; } ;
typedef  int /*<<< orphan*/  output ;
typedef  int /*<<< orphan*/  input ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;
typedef  enum dc_rotation_angle { ____Placeholder_dc_rotation_angle } dc_rotation_angle ;

/* Variables and functions */
 scalar_t__ AMDGPU_TILING_GET (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCC_INDEPENDENT_64B ; 
 int /*<<< orphan*/  DCC_OFFSET_256B ; 
 int /*<<< orphan*/  DCC_PITCH_MAX ; 
 int EINVAL ; 
 int const ROTATION_ANGLE_0 ; 
 int const ROTATION_ANGLE_180 ; 
 int const ROTATION_ANGLE_270 ; 
 int const ROTATION_ANGLE_90 ; 
 int /*<<< orphan*/  SCAN_DIRECTION_HORIZONTAL ; 
 int /*<<< orphan*/  SCAN_DIRECTION_VERTICAL ; 
 int const SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 
 int /*<<< orphan*/  get_dcc_address (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dc_surface_dcc_cap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct dc_surface_dcc_cap*,struct dc_surface_dcc_cap*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fill_plane_dcc_attributes(struct amdgpu_device *adev,
			  const struct amdgpu_framebuffer *afb,
			  const enum surface_pixel_format format,
			  const enum dc_rotation_angle rotation,
			  const struct plane_size *plane_size,
			  const union dc_tiling_info *tiling_info,
			  const uint64_t info,
			  struct dc_plane_dcc_param *dcc,
			  struct dc_plane_address *address)
{
	struct dc *dc = adev->dm.dc;
	struct dc_dcc_surface_param input;
	struct dc_surface_dcc_cap output;
	uint32_t offset = AMDGPU_TILING_GET(info, DCC_OFFSET_256B);
	uint32_t i64b = AMDGPU_TILING_GET(info, DCC_INDEPENDENT_64B) != 0;
	uint64_t dcc_address;

	memset(&input, 0, sizeof(input));
	memset(&output, 0, sizeof(output));

	if (!offset)
		return 0;

	if (format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		return 0;

	if (!dc->cap_funcs.get_dcc_compression_cap)
		return -EINVAL;

	input.format = format;
	input.surface_size.width = plane_size->surface_size.width;
	input.surface_size.height = plane_size->surface_size.height;
	input.swizzle_mode = tiling_info->gfx9.swizzle;

	if (rotation == ROTATION_ANGLE_0 || rotation == ROTATION_ANGLE_180)
		input.scan = SCAN_DIRECTION_HORIZONTAL;
	else if (rotation == ROTATION_ANGLE_90 || rotation == ROTATION_ANGLE_270)
		input.scan = SCAN_DIRECTION_VERTICAL;

	if (!dc->cap_funcs.get_dcc_compression_cap(dc, &input, &output))
		return -EINVAL;

	if (!output.capable)
		return -EINVAL;

	if (i64b == 0 && output.grph.rgb.independent_64b_blks != 0)
		return -EINVAL;

	dcc->enable = 1;
	dcc->meta_pitch =
		AMDGPU_TILING_GET(info, DCC_PITCH_MAX) + 1;
	dcc->independent_64b_blks = i64b;

	dcc_address = get_dcc_address(afb->address, info);
	address->grph.meta_addr.low_part = lower_32_bits(dcc_address);
	address->grph.meta_addr.high_part = upper_32_bits(dcc_address);

	return 0;
}