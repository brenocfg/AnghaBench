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
struct drm_property_blob {int dummy; } ;
struct drm_plane_state {struct drm_property_blob* fb_damage_clips; } ;

/* Variables and functions */

__attribute__((used)) static void set_plane_damage(struct drm_plane_state *state,
			     struct drm_property_blob *damage_blob)
{
	state->fb_damage_clips = damage_blob;
}