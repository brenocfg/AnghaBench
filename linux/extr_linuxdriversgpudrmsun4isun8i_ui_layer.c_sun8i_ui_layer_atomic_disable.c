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
struct sun8i_ui_layer {int /*<<< orphan*/  overlay; int /*<<< orphan*/  channel; struct sun8i_mixer* mixer; } ;
struct sun8i_mixer {int dummy; } ;
struct drm_plane_state {unsigned int normalized_zpos; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 struct sun8i_ui_layer* plane_to_sun8i_ui_layer (struct drm_plane*) ; 
 int /*<<< orphan*/  sun8i_ui_layer_enable (struct sun8i_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sun8i_ui_layer_atomic_disable(struct drm_plane *plane,
					  struct drm_plane_state *old_state)
{
	struct sun8i_ui_layer *layer = plane_to_sun8i_ui_layer(plane);
	unsigned int old_zpos = old_state->normalized_zpos;
	struct sun8i_mixer *mixer = layer->mixer;

	sun8i_ui_layer_enable(mixer, layer->channel, layer->overlay, false, 0,
			      old_zpos);
}