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
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void vc4_plane_atomic_update(struct drm_plane *plane,
				    struct drm_plane_state *old_state)
{
	/* No contents here.  Since we don't know where in the CRTC's
	 * dlist we should be stored, our dlist is uploaded to the
	 * hardware with vc4_plane_write_dlist() at CRTC atomic_flush
	 * time.
	 */
}