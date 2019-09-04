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
struct vlv_fifo_state {scalar_t__* plane; } ;
struct TYPE_3__ {struct vlv_fifo_state fifo_state; struct g4x_pipe_wm* raw; } ;
struct TYPE_4__ {TYPE_1__ vlv; } ;
struct intel_crtc_state {TYPE_2__ wm; } ;
struct g4x_pipe_wm {scalar_t__* plane; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;

/* Variables and functions */

__attribute__((used)) static bool vlv_raw_plane_wm_is_valid(const struct intel_crtc_state *crtc_state,
				      enum plane_id plane_id, int level)
{
	const struct g4x_pipe_wm *raw =
		&crtc_state->wm.vlv.raw[level];
	const struct vlv_fifo_state *fifo_state =
		&crtc_state->wm.vlv.fifo_state;

	return raw->plane[plane_id] <= fifo_state->plane[plane_id];
}