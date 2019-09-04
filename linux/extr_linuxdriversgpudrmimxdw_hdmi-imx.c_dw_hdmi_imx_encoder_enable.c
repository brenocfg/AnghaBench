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
struct imx_hdmi {int /*<<< orphan*/  regmap; TYPE_1__* dev; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX6Q_GPR3_HDMI_MUX_CTL_MASK ; 
 int IMX6Q_GPR3_HDMI_MUX_CTL_SHIFT ; 
 int /*<<< orphan*/  IOMUXC_GPR3 ; 
 int drm_of_encoder_active_port_id (int /*<<< orphan*/ ,struct drm_encoder*) ; 
 struct imx_hdmi* enc_to_imx_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_hdmi_imx_encoder_enable(struct drm_encoder *encoder)
{
	struct imx_hdmi *hdmi = enc_to_imx_hdmi(encoder);
	int mux = drm_of_encoder_active_port_id(hdmi->dev->of_node, encoder);

	regmap_update_bits(hdmi->regmap, IOMUXC_GPR3,
			   IMX6Q_GPR3_HDMI_MUX_CTL_MASK,
			   mux << IMX6Q_GPR3_HDMI_MUX_CTL_SHIFT);
}