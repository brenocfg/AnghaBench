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
struct vc4_hdmi {TYPE_1__* pdev; int /*<<< orphan*/  pixel_clock; } ;
struct vc4_dev {struct vc4_hdmi* hdmi; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 
 int HD_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HD_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VC4_HDMI_RAM_PACKET_CONFIG ; 
 int /*<<< orphan*/  VC4_HDMI_TX_PHY_RESET_CTL ; 
 int /*<<< orphan*/  VC4_HD_VID_CTL ; 
 int VC4_HD_VID_CTL_ENABLE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int pm_runtime_put (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void vc4_hdmi_encoder_disable(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_hdmi *hdmi = vc4->hdmi;
	int ret;

	HDMI_WRITE(VC4_HDMI_RAM_PACKET_CONFIG, 0);

	HDMI_WRITE(VC4_HDMI_TX_PHY_RESET_CTL, 0xf << 16);
	HD_WRITE(VC4_HD_VID_CTL,
		 HD_READ(VC4_HD_VID_CTL) & ~VC4_HD_VID_CTL_ENABLE);

	clk_disable_unprepare(hdmi->pixel_clock);

	ret = pm_runtime_put(&hdmi->pdev->dev);
	if (ret < 0)
		DRM_ERROR("Failed to release power domain: %d\n", ret);
}