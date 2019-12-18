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
struct radeon_device {scalar_t__ family; } ;
struct radeon_bo {int dummy; } ;
struct r100_cs_track {unsigned int num_texture; TYPE_1__* textures; int /*<<< orphan*/  separate_cube; } ;
struct TYPE_2__ {unsigned int num_levels; int pitch; int cpp; unsigned int width; unsigned int width_11; unsigned int height; unsigned int height_11; int tex_coord_type; int txdepth; scalar_t__ compress_format; scalar_t__ roundup_h; scalar_t__ roundup_w; scalar_t__ use_pitch; struct radeon_bo* robj; scalar_t__ lookup_disable; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 scalar_t__ CHIP_R300 ; 
 scalar_t__ CHIP_RV515 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,...) ; 
 int EINVAL ; 
 int r100_cs_track_cube (struct radeon_device*,struct r100_cs_track*,unsigned int) ; 
 int /*<<< orphan*/  r100_cs_track_texture_print (TYPE_1__*) ; 
 unsigned int r100_track_compress_size (scalar_t__,unsigned int,unsigned int) ; 
 unsigned long radeon_bo_size (struct radeon_bo*) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 

__attribute__((used)) static int r100_cs_track_texture_check(struct radeon_device *rdev,
				       struct r100_cs_track *track)
{
	struct radeon_bo *robj;
	unsigned long size;
	unsigned u, i, w, h, d;
	int ret;

	for (u = 0; u < track->num_texture; u++) {
		if (!track->textures[u].enabled)
			continue;
		if (track->textures[u].lookup_disable)
			continue;
		robj = track->textures[u].robj;
		if (robj == NULL) {
			DRM_ERROR("No texture bound to unit %u\n", u);
			return -EINVAL;
		}
		size = 0;
		for (i = 0; i <= track->textures[u].num_levels; i++) {
			if (track->textures[u].use_pitch) {
				if (rdev->family < CHIP_R300)
					w = (track->textures[u].pitch / track->textures[u].cpp) / (1 << i);
				else
					w = track->textures[u].pitch / (1 << i);
			} else {
				w = track->textures[u].width;
				if (rdev->family >= CHIP_RV515)
					w |= track->textures[u].width_11;
				w = w / (1 << i);
				if (track->textures[u].roundup_w)
					w = roundup_pow_of_two(w);
			}
			h = track->textures[u].height;
			if (rdev->family >= CHIP_RV515)
				h |= track->textures[u].height_11;
			h = h / (1 << i);
			if (track->textures[u].roundup_h)
				h = roundup_pow_of_two(h);
			if (track->textures[u].tex_coord_type == 1) {
				d = (1 << track->textures[u].txdepth) / (1 << i);
				if (!d)
					d = 1;
			} else {
				d = 1;
			}
			if (track->textures[u].compress_format) {

				size += r100_track_compress_size(track->textures[u].compress_format, w, h) * d;
				/* compressed textures are block based */
			} else
				size += w * h * d;
		}
		size *= track->textures[u].cpp;

		switch (track->textures[u].tex_coord_type) {
		case 0:
		case 1:
			break;
		case 2:
			if (track->separate_cube) {
				ret = r100_cs_track_cube(rdev, track, u);
				if (ret)
					return ret;
			} else
				size *= 6;
			break;
		default:
			DRM_ERROR("Invalid texture coordinate type %u for unit "
				  "%u\n", track->textures[u].tex_coord_type, u);
			return -EINVAL;
		}
		if (size > radeon_bo_size(robj)) {
			DRM_ERROR("Texture of unit %u needs %lu bytes but is "
				  "%lu\n", u, size, radeon_bo_size(robj));
			r100_cs_track_texture_print(&track->textures[u]);
			return -EINVAL;
		}
	}
	return 0;
}