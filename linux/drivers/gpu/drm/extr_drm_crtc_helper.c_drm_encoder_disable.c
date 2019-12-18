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
struct drm_encoder_helper_funcs {int /*<<< orphan*/  (* dpms ) (struct drm_encoder*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable ) (struct drm_encoder*) ;} ;
struct drm_encoder {struct drm_encoder_helper_funcs* helper_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub2 (struct drm_encoder*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
drm_encoder_disable(struct drm_encoder *encoder)
{
	const struct drm_encoder_helper_funcs *encoder_funcs = encoder->helper_private;

	if (!encoder_funcs)
		return;

	if (encoder_funcs->disable)
		(*encoder_funcs->disable)(encoder);
	else if (encoder_funcs->dpms)
		(*encoder_funcs->dpms)(encoder, DRM_MODE_DPMS_OFF);
}