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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sun4i_layer {TYPE_1__* backend; } ;
struct drm_plane {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  frontend; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct sun4i_layer* plane_to_sun4i_layer (struct drm_plane*) ; 
 scalar_t__ sun4i_backend_format_is_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sun4i_frontend_format_is_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sun4i_layer_format_mod_supported(struct drm_plane *plane,
					     uint32_t format, uint64_t modifier)
{
	struct sun4i_layer *layer = plane_to_sun4i_layer(plane);

	if (IS_ERR_OR_NULL(layer->backend->frontend))
		sun4i_backend_format_is_supported(format, modifier);

	return sun4i_backend_format_is_supported(format, modifier) ||
	       sun4i_frontend_format_is_supported(format, modifier);
}