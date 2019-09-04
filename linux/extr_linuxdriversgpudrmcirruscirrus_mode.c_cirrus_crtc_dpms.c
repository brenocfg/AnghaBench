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
struct drm_device {struct cirrus_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct cirrus_device {int dummy; } ;

/* Variables and functions */
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  GFX_DATA ; 
 int /*<<< orphan*/  GFX_INDEX ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_DATA ; 
 int /*<<< orphan*/  SEQ_INDEX ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG_GFX (int,int) ; 
 int /*<<< orphan*/  WREG_SEQ (int,int) ; 

__attribute__((used)) static void cirrus_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct cirrus_device *cdev = dev->dev_private;
	u8 sr01, gr0e;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		sr01 = 0x00;
		gr0e = 0x00;
		break;
	case DRM_MODE_DPMS_STANDBY:
		sr01 = 0x20;
		gr0e = 0x02;
		break;
	case DRM_MODE_DPMS_SUSPEND:
		sr01 = 0x20;
		gr0e = 0x04;
		break;
	case DRM_MODE_DPMS_OFF:
		sr01 = 0x20;
		gr0e = 0x06;
		break;
	default:
		return;
	}

	WREG8(SEQ_INDEX, 0x1);
	sr01 |= RREG8(SEQ_DATA) & ~0x20;
	WREG_SEQ(0x1, sr01);

	WREG8(GFX_INDEX, 0xe);
	gr0e |= RREG8(GFX_DATA) & ~0x06;
	WREG_GFX(0xe, gr0e);
}