#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_property_blob {scalar_t__ data; } ;
struct drm_color_ctm {unsigned long long* matrix; } ;
struct TYPE_4__ {struct drm_property_blob* ctm; } ;
struct dm_crtc_state {struct dc_stream_state* stream; TYPE_1__ base; } ;
struct TYPE_5__ {int enable_remap; TYPE_3__* matrix; } ;
struct dc_stream_state {TYPE_2__ gamut_remap_matrix; } ;
typedef  unsigned long long int64_t ;
struct TYPE_6__ {unsigned long long value; } ;

/* Variables and functions */
 TYPE_3__ dc_fixpt_zero ; 

void amdgpu_dm_set_ctm(struct dm_crtc_state *crtc)
{

	struct drm_property_blob *blob = crtc->base.ctm;
	struct dc_stream_state *stream = crtc->stream;
	struct drm_color_ctm *ctm;
	int64_t val;
	int i;

	if (!blob) {
		stream->gamut_remap_matrix.enable_remap = false;
		return;
	}

	stream->gamut_remap_matrix.enable_remap = true;
	ctm = (struct drm_color_ctm *)blob->data;
	/*
	 * DRM gives a 3x3 matrix, but DC wants 3x4. Assuming we're operating
	 * with homogeneous coordinates, augment the matrix with 0's.
	 *
	 * The format provided is S31.32, using signed-magnitude representation.
	 * Our fixed31_32 is also S31.32, but is using 2's complement. We have
	 * to convert from signed-magnitude to 2's complement.
	 */
	for (i = 0; i < 12; i++) {
		/* Skip 4th element */
		if (i % 4 == 3) {
			stream->gamut_remap_matrix.matrix[i] = dc_fixpt_zero;
			continue;
		}

		/* gamut_remap_matrix[i] = ctm[i - floor(i/4)] */
		val = ctm->matrix[i - (i/4)];
		/* If negative, convert to 2's complement. */
		if (val & (1ULL << 63))
			val = -(val & ~(1ULL << 63));

		stream->gamut_remap_matrix.matrix[i].value = val;
	}
}