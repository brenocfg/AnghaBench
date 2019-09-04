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
struct sti_fps_info {int curr_field_counter; int curr_frame_counter; int last_frame_counter; int last_field_counter; char* fips_str; int /*<<< orphan*/  fps_str; scalar_t__ output; int /*<<< orphan*/  last_timestamp; } ;
struct TYPE_4__ {char* name; struct drm_plane_state* state; } ;
struct sti_plane {struct sti_fps_info fps_info; TYPE_1__ drm_plane; } ;
struct drm_plane_state {TYPE_3__* fb; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_6__ {int width; int height; TYPE_2__* format; } ;
struct TYPE_5__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FPS_LENGTH ; 
 int STI_FPS_INTERVAL_MS ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 char* sti_plane_to_str (struct sti_plane*) ; 

void sti_plane_update_fps(struct sti_plane *plane,
			  bool new_frame,
			  bool new_field)
{
	struct drm_plane_state *state = plane->drm_plane.state;
	ktime_t now;
	struct sti_fps_info *fps;
	int fpks, fipks, ms_since_last, num_frames, num_fields;

	now = ktime_get();

	/* Compute number of frame updates */
	fps = &plane->fps_info;

	if (new_field)
		fps->curr_field_counter++;

	/* do not perform fps calcul if new_frame is false */
	if (!new_frame)
		return;

	fps->curr_frame_counter++;
	ms_since_last = ktime_to_ms(ktime_sub(now, fps->last_timestamp));
	num_frames = fps->curr_frame_counter - fps->last_frame_counter;

	if (num_frames <= 0  || ms_since_last < STI_FPS_INTERVAL_MS)
		return;

	fps->last_timestamp = now;
	fps->last_frame_counter = fps->curr_frame_counter;

	if (state->fb) {
		fpks = (num_frames * 1000000) / ms_since_last;
		snprintf(plane->fps_info.fps_str, FPS_LENGTH,
			 "%-8s %4dx%-4d %.4s @ %3d.%-3.3d fps (%s)",
			 plane->drm_plane.name,
			 state->fb->width,
			 state->fb->height,
			 (char *)&state->fb->format->format,
			 fpks / 1000, fpks % 1000,
			 sti_plane_to_str(plane));
	}

	if (fps->curr_field_counter) {
		/* Compute number of field updates */
		num_fields = fps->curr_field_counter - fps->last_field_counter;
		fps->last_field_counter = fps->curr_field_counter;
		fipks = (num_fields * 1000000) / ms_since_last;
		snprintf(plane->fps_info.fips_str,
			 FPS_LENGTH, " - %3d.%-3.3d field/sec",
			 fipks / 1000, fipks % 1000);
	} else {
		plane->fps_info.fips_str[0] = '\0';
	}

	if (fps->output)
		DRM_INFO("%s%s\n",
			 plane->fps_info.fps_str,
			 plane->fps_info.fips_str);
}