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
struct videomode {scalar_t__ vsync_len; scalar_t__ hsync_len; } ;
struct ipu_crtc {int /*<<< orphan*/  di; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_display_mode_from_videomode (struct videomode*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_display_mode_to_videomode (struct drm_display_mode*,struct videomode*) ; 
 int ipu_di_adjust_videomode (int /*<<< orphan*/ ,struct videomode*) ; 
 struct ipu_crtc* to_ipu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static bool ipu_crtc_mode_fixup(struct drm_crtc *crtc,
				  const struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode)
{
	struct ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);
	struct videomode vm;
	int ret;

	drm_display_mode_to_videomode(adjusted_mode, &vm);

	ret = ipu_di_adjust_videomode(ipu_crtc->di, &vm);
	if (ret)
		return false;

	if ((vm.vsync_len == 0) || (vm.hsync_len == 0))
		return false;

	drm_display_mode_from_videomode(&vm, adjusted_mode);

	return true;
}