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
typedef  scalar_t__ uint32_t ;
struct simplefb_format {scalar_t__ fourcc; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
struct drm_crtc {TYPE_2__* primary; } ;
struct arcpgu_drm_private {int dummy; } ;
struct TYPE_6__ {scalar_t__ format; } ;
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_4__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int ARCPGU_MODE_RGB888_MASK ; 
 int /*<<< orphan*/  ARCPGU_REG_CTRL ; 
 int ARRAY_SIZE (struct simplefb_format*) ; 
 scalar_t__ DRM_FORMAT_RGB888 ; 
 scalar_t__ WARN_ON (int) ; 
 int arc_pgu_read (struct arcpgu_drm_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_pgu_write (struct arcpgu_drm_private*,int /*<<< orphan*/ ,int) ; 
 struct arcpgu_drm_private* crtc_to_arcpgu_priv (struct drm_crtc*) ; 
 struct simplefb_format* supported_formats ; 

__attribute__((used)) static void arc_pgu_set_pxl_fmt(struct drm_crtc *crtc)
{
	struct arcpgu_drm_private *arcpgu = crtc_to_arcpgu_priv(crtc);
	const struct drm_framebuffer *fb = crtc->primary->state->fb;
	uint32_t pixel_format = fb->format->format;
	struct simplefb_format *format = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(supported_formats); i++) {
		if (supported_formats[i].fourcc == pixel_format)
			format = &supported_formats[i];
	}

	if (WARN_ON(!format))
		return;

	if (format->fourcc == DRM_FORMAT_RGB888)
		arc_pgu_write(arcpgu, ARCPGU_REG_CTRL,
			      arc_pgu_read(arcpgu, ARCPGU_REG_CTRL) |
					   ARCPGU_MODE_RGB888_MASK);

}