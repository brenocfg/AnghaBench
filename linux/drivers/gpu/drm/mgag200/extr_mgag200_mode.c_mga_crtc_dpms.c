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
typedef  int u8 ;
struct mga_device {int suspended; } ;
struct drm_device {struct mga_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  MGAREG_CRTCEXT_DATA ; 
 int /*<<< orphan*/  MGAREG_CRTCEXT_INDEX ; 
 int /*<<< orphan*/  MGAREG_SEQ_DATA ; 
 int /*<<< orphan*/  MGAREG_SEQ_INDEX ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_helper_resume_force_mode (struct drm_device*) ; 
 int /*<<< orphan*/  mga_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  mga_resume (struct drm_crtc*) ; 
 int /*<<< orphan*/  mga_suspend (struct drm_crtc*) ; 
 int /*<<< orphan*/  mga_wait_busy (struct mga_device*) ; 
 int /*<<< orphan*/  mga_wait_vsync (struct mga_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void mga_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct mga_device *mdev = dev->dev_private;
	u8 seq1 = 0, crtcext1 = 0;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		seq1 = 0;
		crtcext1 = 0;
		mga_crtc_load_lut(crtc);
		break;
	case DRM_MODE_DPMS_STANDBY:
		seq1 = 0x20;
		crtcext1 = 0x10;
		break;
	case DRM_MODE_DPMS_SUSPEND:
		seq1 = 0x20;
		crtcext1 = 0x20;
		break;
	case DRM_MODE_DPMS_OFF:
		seq1 = 0x20;
		crtcext1 = 0x30;
		break;
	}

#if 0
	if (mode == DRM_MODE_DPMS_OFF) {
		mga_suspend(crtc);
	}
#endif
	WREG8(MGAREG_SEQ_INDEX, 0x01);
	seq1 |= RREG8(MGAREG_SEQ_DATA) & ~0x20;
	mga_wait_vsync(mdev);
	mga_wait_busy(mdev);
	WREG8(MGAREG_SEQ_DATA, seq1);
	msleep(20);
	WREG8(MGAREG_CRTCEXT_INDEX, 0x01);
	crtcext1 |= RREG8(MGAREG_CRTCEXT_DATA) & ~0x30;
	WREG8(MGAREG_CRTCEXT_DATA, crtcext1);

#if 0
	if (mode == DRM_MODE_DPMS_ON && mdev->suspended == true) {
		mga_resume(crtc);
		drm_helper_resume_force_mode(dev);
	}
#endif
}