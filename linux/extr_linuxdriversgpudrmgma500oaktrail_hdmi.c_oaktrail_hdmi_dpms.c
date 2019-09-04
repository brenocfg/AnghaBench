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
typedef  int u32 ;
struct oaktrail_hdmi_dev {int dummy; } ;
struct drm_psb_private {struct oaktrail_hdmi_dev* hdmi_priv; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  HDMI_VIDEO_REG ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void oaktrail_hdmi_dpms(struct drm_encoder *encoder, int mode)
{
	static int dpms_mode = -1;

	struct drm_device *dev = encoder->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	u32 temp;

	if (dpms_mode == mode)
		return;

	if (mode != DRM_MODE_DPMS_ON)
		temp = 0x0;
	else
		temp = 0x99;

	dpms_mode = mode;
	HDMI_WRITE(HDMI_VIDEO_REG, temp);
}