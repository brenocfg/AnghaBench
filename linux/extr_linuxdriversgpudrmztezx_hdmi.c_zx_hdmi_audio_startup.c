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
struct drm_encoder {int /*<<< orphan*/  crtc; } ;
struct zx_hdmi {struct drm_encoder encoder; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOU_HDMI_AUD_SPDIF ; 
 struct zx_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  vou_inf_hdmi_audio_sel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_hdmi_audio_startup(struct device *dev, void *data)
{
	struct zx_hdmi *hdmi = dev_get_drvdata(dev);
	struct drm_encoder *encoder = &hdmi->encoder;

	vou_inf_hdmi_audio_sel(encoder->crtc, VOU_HDMI_AUD_SPDIF);

	return 0;
}