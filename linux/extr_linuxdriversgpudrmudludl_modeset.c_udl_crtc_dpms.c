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
struct urb {scalar_t__ transfer_buffer; } ;
struct udl_device {scalar_t__ mode_buf_len; } ;
struct drm_device {struct udl_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  udl_crtc_write_mode_to_hw (struct drm_crtc*) ; 
 char* udl_dummy_render (char*) ; 
 struct urb* udl_get_urb (struct drm_device*) ; 
 char* udl_set_blank (char*,int) ; 
 int udl_submit_urb (struct drm_device*,struct urb*,int) ; 
 char* udl_vidreg_lock (char*) ; 
 char* udl_vidreg_unlock (char*) ; 

__attribute__((used)) static void udl_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct udl_device *udl = dev->dev_private;
	int retval;

	if (mode == DRM_MODE_DPMS_OFF) {
		char *buf;
		struct urb *urb;
		urb = udl_get_urb(dev);
		if (!urb)
			return;

		buf = (char *)urb->transfer_buffer;
		buf = udl_vidreg_lock(buf);
		buf = udl_set_blank(buf, mode);
		buf = udl_vidreg_unlock(buf);

		buf = udl_dummy_render(buf);
		retval = udl_submit_urb(dev, urb, buf - (char *)
					urb->transfer_buffer);
	} else {
		if (udl->mode_buf_len == 0) {
			DRM_ERROR("Trying to enable DPMS with no mode\n");
			return;
		}
		udl_crtc_write_mode_to_hw(crtc);
	}

}