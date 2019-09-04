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
struct mid_intel_hdmi_priv {int /*<<< orphan*/  hdmi_reg; int /*<<< orphan*/  save_HDMIB; } ;
struct gma_encoder {struct mid_intel_hdmi_priv* dev_priv; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 

__attribute__((used)) static void cdv_hdmi_save(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct gma_encoder *gma_encoder = gma_attached_encoder(connector);
	struct mid_intel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;

	hdmi_priv->save_HDMIB = REG_READ(hdmi_priv->hdmi_reg);
}