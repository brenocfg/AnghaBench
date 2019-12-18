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
struct sun8i_ui_layer {int /*<<< orphan*/  overlay; int /*<<< orphan*/  channel; struct sun8i_mixer* mixer; } ;
struct sun8i_mixer {int dummy; } ;
struct drm_plane_state {unsigned int normalized_zpos; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_2__ {unsigned int normalized_zpos; int /*<<< orphan*/  visible; } ;

/* Variables and functions */
 struct sun8i_ui_layer* plane_to_sun8i_ui_layer (struct drm_plane*) ; 
 int /*<<< orphan*/  sun8i_ui_layer_enable (struct sun8i_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sun8i_ui_layer_update_buffer (struct sun8i_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_plane*) ; 
 int /*<<< orphan*/  sun8i_ui_layer_update_coord (struct sun8i_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_plane*,unsigned int) ; 
 int /*<<< orphan*/  sun8i_ui_layer_update_formats (struct sun8i_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_plane*) ; 

__attribute__((used)) static void sun8i_ui_layer_atomic_update(struct drm_plane *plane,
					 struct drm_plane_state *old_state)
{
	struct sun8i_ui_layer *layer = plane_to_sun8i_ui_layer(plane);
	unsigned int zpos = plane->state->normalized_zpos;
	unsigned int old_zpos = old_state->normalized_zpos;
	struct sun8i_mixer *mixer = layer->mixer;

	if (!plane->state->visible) {
		sun8i_ui_layer_enable(mixer, layer->channel,
				      layer->overlay, false, 0, old_zpos);
		return;
	}

	sun8i_ui_layer_update_coord(mixer, layer->channel,
				    layer->overlay, plane, zpos);
	sun8i_ui_layer_update_formats(mixer, layer->channel,
				      layer->overlay, plane);
	sun8i_ui_layer_update_buffer(mixer, layer->channel,
				     layer->overlay, plane);
	sun8i_ui_layer_enable(mixer, layer->channel, layer->overlay,
			      true, zpos, old_zpos);
}