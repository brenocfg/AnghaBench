#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {unsigned long pitch; unsigned long offset; int /*<<< orphan*/ * robj; } ;
struct TYPE_6__ {unsigned long pitch; unsigned long cpp; unsigned long offset; int /*<<< orphan*/ * robj; } ;
struct r100_cs_track {int cb_dirty; unsigned int num_cb; unsigned long maxy; int zb_dirty; int aa_dirty; int vap_vf_cntl; unsigned int vap_alt_nverts; unsigned int num_arrays; int max_indx; unsigned int vtx_size; unsigned long immd_dwords; int tex_dirty; TYPE_1__* arrays; TYPE_4__ aa; TYPE_3__* cb; scalar_t__ aaresolve; TYPE_2__ zb; scalar_t__ z_enabled; int /*<<< orphan*/  blend_read_enable; int /*<<< orphan*/  color_channel_mask; int /*<<< orphan*/  zb_cb_clear; } ;
struct TYPE_7__ {unsigned long pitch; unsigned long cpp; scalar_t__ offset; int /*<<< orphan*/ * robj; } ;
struct TYPE_5__ {int esize; int /*<<< orphan*/ * robj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned long,int) ; 
 int r100_cs_track_texture_check (struct radeon_device*,struct r100_cs_track*) ; 
 int radeon_bo_size (int /*<<< orphan*/ *) ; 

int r100_cs_track_check(struct radeon_device *rdev, struct r100_cs_track *track)
{
	unsigned i;
	unsigned long size;
	unsigned prim_walk;
	unsigned nverts;
	unsigned num_cb = track->cb_dirty ? track->num_cb : 0;

	if (num_cb && !track->zb_cb_clear && !track->color_channel_mask &&
	    !track->blend_read_enable)
		num_cb = 0;

	for (i = 0; i < num_cb; i++) {
		if (track->cb[i].robj == NULL) {
			DRM_ERROR("[drm] No buffer for color buffer %d !\n", i);
			return -EINVAL;
		}
		size = track->cb[i].pitch * track->cb[i].cpp * track->maxy;
		size += track->cb[i].offset;
		if (size > radeon_bo_size(track->cb[i].robj)) {
			DRM_ERROR("[drm] Buffer too small for color buffer %d "
				  "(need %lu have %lu) !\n", i, size,
				  radeon_bo_size(track->cb[i].robj));
			DRM_ERROR("[drm] color buffer %d (%u %u %u %u)\n",
				  i, track->cb[i].pitch, track->cb[i].cpp,
				  track->cb[i].offset, track->maxy);
			return -EINVAL;
		}
	}
	track->cb_dirty = false;

	if (track->zb_dirty && track->z_enabled) {
		if (track->zb.robj == NULL) {
			DRM_ERROR("[drm] No buffer for z buffer !\n");
			return -EINVAL;
		}
		size = track->zb.pitch * track->zb.cpp * track->maxy;
		size += track->zb.offset;
		if (size > radeon_bo_size(track->zb.robj)) {
			DRM_ERROR("[drm] Buffer too small for z buffer "
				  "(need %lu have %lu) !\n", size,
				  radeon_bo_size(track->zb.robj));
			DRM_ERROR("[drm] zbuffer (%u %u %u %u)\n",
				  track->zb.pitch, track->zb.cpp,
				  track->zb.offset, track->maxy);
			return -EINVAL;
		}
	}
	track->zb_dirty = false;

	if (track->aa_dirty && track->aaresolve) {
		if (track->aa.robj == NULL) {
			DRM_ERROR("[drm] No buffer for AA resolve buffer %d !\n", i);
			return -EINVAL;
		}
		/* I believe the format comes from colorbuffer0. */
		size = track->aa.pitch * track->cb[0].cpp * track->maxy;
		size += track->aa.offset;
		if (size > radeon_bo_size(track->aa.robj)) {
			DRM_ERROR("[drm] Buffer too small for AA resolve buffer %d "
				  "(need %lu have %lu) !\n", i, size,
				  radeon_bo_size(track->aa.robj));
			DRM_ERROR("[drm] AA resolve buffer %d (%u %u %u %u)\n",
				  i, track->aa.pitch, track->cb[0].cpp,
				  track->aa.offset, track->maxy);
			return -EINVAL;
		}
	}
	track->aa_dirty = false;

	prim_walk = (track->vap_vf_cntl >> 4) & 0x3;
	if (track->vap_vf_cntl & (1 << 14)) {
		nverts = track->vap_alt_nverts;
	} else {
		nverts = (track->vap_vf_cntl >> 16) & 0xFFFF;
	}
	switch (prim_walk) {
	case 1:
		for (i = 0; i < track->num_arrays; i++) {
			size = track->arrays[i].esize * track->max_indx * 4;
			if (track->arrays[i].robj == NULL) {
				DRM_ERROR("(PW %u) Vertex array %u no buffer "
					  "bound\n", prim_walk, i);
				return -EINVAL;
			}
			if (size > radeon_bo_size(track->arrays[i].robj)) {
				dev_err(rdev->dev, "(PW %u) Vertex array %u "
					"need %lu dwords have %lu dwords\n",
					prim_walk, i, size >> 2,
					radeon_bo_size(track->arrays[i].robj)
					>> 2);
				DRM_ERROR("Max indices %u\n", track->max_indx);
				return -EINVAL;
			}
		}
		break;
	case 2:
		for (i = 0; i < track->num_arrays; i++) {
			size = track->arrays[i].esize * (nverts - 1) * 4;
			if (track->arrays[i].robj == NULL) {
				DRM_ERROR("(PW %u) Vertex array %u no buffer "
					  "bound\n", prim_walk, i);
				return -EINVAL;
			}
			if (size > radeon_bo_size(track->arrays[i].robj)) {
				dev_err(rdev->dev, "(PW %u) Vertex array %u "
					"need %lu dwords have %lu dwords\n",
					prim_walk, i, size >> 2,
					radeon_bo_size(track->arrays[i].robj)
					>> 2);
				return -EINVAL;
			}
		}
		break;
	case 3:
		size = track->vtx_size * nverts;
		if (size != track->immd_dwords) {
			DRM_ERROR("IMMD draw %u dwors but needs %lu dwords\n",
				  track->immd_dwords, size);
			DRM_ERROR("VAP_VF_CNTL.NUM_VERTICES %u, VTX_SIZE %u\n",
				  nverts, track->vtx_size);
			return -EINVAL;
		}
		break;
	default:
		DRM_ERROR("[drm] Invalid primitive walk %d for VAP_VF_CNTL\n",
			  prim_walk);
		return -EINVAL;
	}

	if (track->tex_dirty) {
		track->tex_dirty = false;
		return r100_cs_track_texture_check(rdev, track);
	}
	return 0;
}