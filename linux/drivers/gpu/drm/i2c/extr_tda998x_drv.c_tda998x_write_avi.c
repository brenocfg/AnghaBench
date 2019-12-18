#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  quantization_range; } ;
union hdmi_infoframe {TYPE_1__ avi; } ;
struct tda998x_priv {int /*<<< orphan*/  rgb_quant_range; int /*<<< orphan*/  connector; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIP_IF_FLAGS_IF2 ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_FULL ; 
 int /*<<< orphan*/  REG_IF2_HB0 ; 
 int /*<<< orphan*/  drm_hdmi_avi_infoframe_from_display_mode (TYPE_1__*,int /*<<< orphan*/ *,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_hdmi_avi_infoframe_quant_range (TYPE_1__*,int /*<<< orphan*/ *,struct drm_display_mode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda998x_write_if (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union hdmi_infoframe*) ; 

__attribute__((used)) static void
tda998x_write_avi(struct tda998x_priv *priv, const struct drm_display_mode *mode)
{
	union hdmi_infoframe frame;

	drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						 &priv->connector, mode);
	frame.avi.quantization_range = HDMI_QUANTIZATION_RANGE_FULL;
	drm_hdmi_avi_infoframe_quant_range(&frame.avi, &priv->connector, mode,
					   priv->rgb_quant_range);

	tda998x_write_if(priv, DIP_IF_FLAGS_IF2, REG_IF2_HB0, &frame);
}