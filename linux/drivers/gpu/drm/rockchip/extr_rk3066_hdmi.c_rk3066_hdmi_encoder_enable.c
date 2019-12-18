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
struct rk3066_hdmi {int /*<<< orphan*/  previous_mode; TYPE_1__* dev; int /*<<< orphan*/  grf_regmap; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  GRF_SOC_CON0 ; 
 int HDMI_VIDEO_SEL ; 
 int drm_of_encoder_active_endpoint_id (int /*<<< orphan*/ ,struct drm_encoder*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk3066_hdmi_setup (struct rk3066_hdmi*,int /*<<< orphan*/ *) ; 
 struct rk3066_hdmi* to_rk3066_hdmi (struct drm_encoder*) ; 

__attribute__((used)) static void rk3066_hdmi_encoder_enable(struct drm_encoder *encoder)
{
	struct rk3066_hdmi *hdmi = to_rk3066_hdmi(encoder);
	int mux, val;

	mux = drm_of_encoder_active_endpoint_id(hdmi->dev->of_node, encoder);
	if (mux)
		val = (HDMI_VIDEO_SEL << 16) | HDMI_VIDEO_SEL;
	else
		val = HDMI_VIDEO_SEL << 16;

	regmap_write(hdmi->grf_regmap, GRF_SOC_CON0, val);

	DRM_DEV_DEBUG(hdmi->dev, "hdmi encoder enable select: vop%s\n",
		      (mux) ? "1" : "0");

	rk3066_hdmi_setup(hdmi, &hdmi->previous_mode);
}