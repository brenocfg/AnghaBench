#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct udl_framebuffer {int active_16; TYPE_2__ base; } ;
struct udl_device {int mode_buf_len; scalar_t__ mode_buf; struct drm_crtc* crtc; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int vdisplay; int hdisplay; } ;
struct drm_device {struct udl_device* dev_private; } ;
struct drm_crtc {TYPE_1__* primary; struct drm_device* dev; } ;
struct TYPE_3__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 struct udl_framebuffer* to_udl_fb (struct drm_framebuffer*) ; 
 char* udl_dummy_render (char*) ; 
 int /*<<< orphan*/  udl_handle_damage (struct udl_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* udl_set_base16bpp (char*,int /*<<< orphan*/ ) ; 
 char* udl_set_base8bpp (char*,int) ; 
 char* udl_set_blank (char*,int /*<<< orphan*/ ) ; 
 char* udl_set_color_depth (char*,int) ; 
 char* udl_set_vid_cmds (char*,struct drm_display_mode*) ; 
 char* udl_vidreg_lock (char*) ; 
 char* udl_vidreg_unlock (char*) ; 

__attribute__((used)) static int udl_crtc_mode_set(struct drm_crtc *crtc,
			       struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode,
			       int x, int y,
			       struct drm_framebuffer *old_fb)

{
	struct drm_device *dev = crtc->dev;
	struct udl_framebuffer *ufb = to_udl_fb(crtc->primary->fb);
	struct udl_device *udl = dev->dev_private;
	char *buf;
	char *wrptr;
	int color_depth = 0;

	udl->crtc = crtc;

	buf = (char *)udl->mode_buf;

	/* for now we just clip 24 -> 16 - if we fix that fix this */
	/*if  (crtc->fb->bits_per_pixel != 16)
	  color_depth = 1; */

	/* This first section has to do with setting the base address on the
	* controller * associated with the display. There are 2 base
	* pointers, currently, we only * use the 16 bpp segment.
	*/
	wrptr = udl_vidreg_lock(buf);
	wrptr = udl_set_color_depth(wrptr, color_depth);
	/* set base for 16bpp segment to 0 */
	wrptr = udl_set_base16bpp(wrptr, 0);
	/* set base for 8bpp segment to end of fb */
	wrptr = udl_set_base8bpp(wrptr, 2 * mode->vdisplay * mode->hdisplay);

	wrptr = udl_set_vid_cmds(wrptr, adjusted_mode);
	wrptr = udl_set_blank(wrptr, DRM_MODE_DPMS_ON);
	wrptr = udl_vidreg_unlock(wrptr);

	wrptr = udl_dummy_render(wrptr);

	if (old_fb) {
		struct udl_framebuffer *uold_fb = to_udl_fb(old_fb);
		uold_fb->active_16 = false;
	}
	ufb->active_16 = true;
	udl->mode_buf_len = wrptr - buf;

	/* damage all of it */
	udl_handle_damage(ufb, 0, 0, ufb->base.width, ufb->base.height);
	return 0;
}