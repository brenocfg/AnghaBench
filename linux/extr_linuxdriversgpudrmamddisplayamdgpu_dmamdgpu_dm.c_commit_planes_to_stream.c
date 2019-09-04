#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  updates ;
typedef  int uint8_t ;
struct dm_crtc_state {struct dc_stream_state* stream; } ;
struct dc_surface_update {struct dc_stream_update* scaling_info; struct dc_stream_update* plane_info; struct dc_stream_update* flip_addr; int /*<<< orphan*/  in_transfer_func; struct dc_gamma* gamma; struct dc_plane_state* surface; } ;
struct dc_stream_update {int /*<<< orphan*/  clip_rect; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; int /*<<< orphan*/  scaling_quality; int /*<<< orphan*/  dcc; int /*<<< orphan*/  per_pixel_alpha; int /*<<< orphan*/  visible; int /*<<< orphan*/  tiling_info; int /*<<< orphan*/  stereo_format; int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  rotation; int /*<<< orphan*/  plane_size; int /*<<< orphan*/  format; int /*<<< orphan*/  color_space; int /*<<< orphan*/  flip_immediate; int /*<<< orphan*/  address; int /*<<< orphan*/  out_transfer_func; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct dc_stream_state {int /*<<< orphan*/  out_transfer_func; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct dc_state {int dummy; } ;
struct dc_scaling_info {int /*<<< orphan*/  clip_rect; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; int /*<<< orphan*/  scaling_quality; int /*<<< orphan*/  dcc; int /*<<< orphan*/  per_pixel_alpha; int /*<<< orphan*/  visible; int /*<<< orphan*/  tiling_info; int /*<<< orphan*/  stereo_format; int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  rotation; int /*<<< orphan*/  plane_size; int /*<<< orphan*/  format; int /*<<< orphan*/  color_space; int /*<<< orphan*/  flip_immediate; int /*<<< orphan*/  address; int /*<<< orphan*/  out_transfer_func; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct dc_plane_state {int /*<<< orphan*/  clip_rect; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; int /*<<< orphan*/  scaling_quality; int /*<<< orphan*/  dcc; int /*<<< orphan*/  per_pixel_alpha; int /*<<< orphan*/  visible; int /*<<< orphan*/  tiling_info; int /*<<< orphan*/  stereo_format; int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  rotation; int /*<<< orphan*/  plane_size; int /*<<< orphan*/  format; int /*<<< orphan*/  color_space; int /*<<< orphan*/  flip_immediate; int /*<<< orphan*/  address; int /*<<< orphan*/  in_transfer_func; scalar_t__ gamma_correction; } ;
struct dc_plane_info {int /*<<< orphan*/  clip_rect; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; int /*<<< orphan*/  scaling_quality; int /*<<< orphan*/  dcc; int /*<<< orphan*/  per_pixel_alpha; int /*<<< orphan*/  visible; int /*<<< orphan*/  tiling_info; int /*<<< orphan*/  stereo_format; int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  rotation; int /*<<< orphan*/  plane_size; int /*<<< orphan*/  format; int /*<<< orphan*/  color_space; int /*<<< orphan*/  flip_immediate; int /*<<< orphan*/  address; int /*<<< orphan*/  out_transfer_func; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct dc_gamma {int dummy; } ;
struct dc_flip_addrs {int /*<<< orphan*/  clip_rect; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; int /*<<< orphan*/  scaling_quality; int /*<<< orphan*/  dcc; int /*<<< orphan*/  per_pixel_alpha; int /*<<< orphan*/  visible; int /*<<< orphan*/  tiling_info; int /*<<< orphan*/  stereo_format; int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  rotation; int /*<<< orphan*/  plane_size; int /*<<< orphan*/  format; int /*<<< orphan*/  color_space; int /*<<< orphan*/  flip_immediate; int /*<<< orphan*/  address; int /*<<< orphan*/  out_transfer_func; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_SURFACES ; 
 int /*<<< orphan*/  dc_commit_updates_for_stream (struct dc*,struct dc_surface_update*,int,struct dc_stream_state*,struct dc_stream_update*,struct dc_plane_state**,struct dc_state*) ; 
 struct dc_stream_update* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dc_stream_update*) ; 
 struct dc_stream_update* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dc_surface_update*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool commit_planes_to_stream(
		struct dc *dc,
		struct dc_plane_state **plane_states,
		uint8_t new_plane_count,
		struct dm_crtc_state *dm_new_crtc_state,
		struct dm_crtc_state *dm_old_crtc_state,
		struct dc_state *state)
{
	/* no need to dynamically allocate this. it's pretty small */
	struct dc_surface_update updates[MAX_SURFACES];
	struct dc_flip_addrs *flip_addr;
	struct dc_plane_info *plane_info;
	struct dc_scaling_info *scaling_info;
	int i;
	struct dc_stream_state *dc_stream = dm_new_crtc_state->stream;
	struct dc_stream_update *stream_update =
			kzalloc(sizeof(struct dc_stream_update), GFP_KERNEL);

	if (!stream_update) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	flip_addr = kcalloc(MAX_SURFACES, sizeof(struct dc_flip_addrs),
			    GFP_KERNEL);
	plane_info = kcalloc(MAX_SURFACES, sizeof(struct dc_plane_info),
			     GFP_KERNEL);
	scaling_info = kcalloc(MAX_SURFACES, sizeof(struct dc_scaling_info),
			       GFP_KERNEL);

	if (!flip_addr || !plane_info || !scaling_info) {
		kfree(flip_addr);
		kfree(plane_info);
		kfree(scaling_info);
		kfree(stream_update);
		return false;
	}

	memset(updates, 0, sizeof(updates));

	stream_update->src = dc_stream->src;
	stream_update->dst = dc_stream->dst;
	stream_update->out_transfer_func = dc_stream->out_transfer_func;

	for (i = 0; i < new_plane_count; i++) {
		updates[i].surface = plane_states[i];
		updates[i].gamma =
			(struct dc_gamma *)plane_states[i]->gamma_correction;
		updates[i].in_transfer_func = plane_states[i]->in_transfer_func;
		flip_addr[i].address = plane_states[i]->address;
		flip_addr[i].flip_immediate = plane_states[i]->flip_immediate;
		plane_info[i].color_space = plane_states[i]->color_space;
		plane_info[i].format = plane_states[i]->format;
		plane_info[i].plane_size = plane_states[i]->plane_size;
		plane_info[i].rotation = plane_states[i]->rotation;
		plane_info[i].horizontal_mirror = plane_states[i]->horizontal_mirror;
		plane_info[i].stereo_format = plane_states[i]->stereo_format;
		plane_info[i].tiling_info = plane_states[i]->tiling_info;
		plane_info[i].visible = plane_states[i]->visible;
		plane_info[i].per_pixel_alpha = plane_states[i]->per_pixel_alpha;
		plane_info[i].dcc = plane_states[i]->dcc;
		scaling_info[i].scaling_quality = plane_states[i]->scaling_quality;
		scaling_info[i].src_rect = plane_states[i]->src_rect;
		scaling_info[i].dst_rect = plane_states[i]->dst_rect;
		scaling_info[i].clip_rect = plane_states[i]->clip_rect;

		updates[i].flip_addr = &flip_addr[i];
		updates[i].plane_info = &plane_info[i];
		updates[i].scaling_info = &scaling_info[i];
	}

	dc_commit_updates_for_stream(
			dc,
			updates,
			new_plane_count,
			dc_stream, stream_update, plane_states, state);

	kfree(flip_addr);
	kfree(plane_info);
	kfree(scaling_info);
	kfree(stream_update);
	return true;
}