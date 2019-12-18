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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct dm_crtc_state {scalar_t__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_atomic_helper_crtc_destroy_state (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  dc_stream_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct drm_crtc_state*) ; 
 struct dm_crtc_state* to_dm_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void dm_crtc_destroy_state(struct drm_crtc *crtc,
				  struct drm_crtc_state *state)
{
	struct dm_crtc_state *cur = to_dm_crtc_state(state);

	/* TODO Destroy dc_stream objects are stream object is flattened */
	if (cur->stream)
		dc_stream_release(cur->stream);


	__drm_atomic_helper_crtc_destroy_state(state);


	kfree(state);
}