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
struct drm_encoder_helper_funcs {int (* mode_valid ) (struct drm_encoder*,struct drm_display_mode const*) ;} ;
struct drm_encoder {struct drm_encoder_helper_funcs* helper_private; } ;
struct drm_display_mode {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_OK ; 
 int stub1 (struct drm_encoder*,struct drm_display_mode const*) ; 

enum drm_mode_status drm_encoder_mode_valid(struct drm_encoder *encoder,
					    const struct drm_display_mode *mode)
{
	const struct drm_encoder_helper_funcs *encoder_funcs =
		encoder->helper_private;

	if (!encoder_funcs || !encoder_funcs->mode_valid)
		return MODE_OK;

	return encoder_funcs->mode_valid(encoder, mode);
}