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
struct TYPE_2__ {int /*<<< orphan*/  hdmi; } ;
union hdmi_infoframe {TYPE_1__ vendor; } ;
struct tda998x_priv {int /*<<< orphan*/  connector; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIP_IF_FLAGS_IF1 ; 
 int /*<<< orphan*/  REG_DIP_IF_FLAGS ; 
 int /*<<< orphan*/  REG_IF1_HB0 ; 
 scalar_t__ drm_hdmi_vendor_infoframe_from_display_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  reg_clear (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda998x_write_if (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union hdmi_infoframe*) ; 

__attribute__((used)) static void tda998x_write_vsi(struct tda998x_priv *priv,
			      const struct drm_display_mode *mode)
{
	union hdmi_infoframe frame;

	if (drm_hdmi_vendor_infoframe_from_display_mode(&frame.vendor.hdmi,
							&priv->connector,
							mode))
		reg_clear(priv, REG_DIP_IF_FLAGS, DIP_IF_FLAGS_IF1);
	else
		tda998x_write_if(priv, DIP_IF_FLAGS_IF1, REG_IF1_HB0, &frame);
}