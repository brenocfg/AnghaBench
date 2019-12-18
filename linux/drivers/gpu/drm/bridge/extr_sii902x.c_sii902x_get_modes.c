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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sii902x {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; TYPE_1__* i2cmux; } ;
struct edid {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  display_info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X24 ; 
 int /*<<< orphan*/  SII902X_SYS_CTRL_DATA ; 
 int /*<<< orphan*/  SII902X_SYS_CTRL_OUTPUT_DVI ; 
 int /*<<< orphan*/  SII902X_SYS_CTRL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  SII902X_SYS_CTRL_OUTPUT_MODE ; 
 struct sii902x* connector_to_sii902x (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 scalar_t__ drm_detect_hdmi_monitor (struct edid*) ; 
 int drm_display_info_set_bus_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sii902x_get_modes(struct drm_connector *connector)
{
	struct sii902x *sii902x = connector_to_sii902x(connector);
	u32 bus_format = MEDIA_BUS_FMT_RGB888_1X24;
	u8 output_mode = SII902X_SYS_CTRL_OUTPUT_DVI;
	struct edid *edid;
	int num = 0, ret;

	mutex_lock(&sii902x->mutex);

	edid = drm_get_edid(connector, sii902x->i2cmux->adapter[0]);
	drm_connector_update_edid_property(connector, edid);
	if (edid) {
		if (drm_detect_hdmi_monitor(edid))
			output_mode = SII902X_SYS_CTRL_OUTPUT_HDMI;

		num = drm_add_edid_modes(connector, edid);
		kfree(edid);
	}

	ret = drm_display_info_set_bus_formats(&connector->display_info,
					       &bus_format, 1);
	if (ret)
		goto error_out;

	ret = regmap_update_bits(sii902x->regmap, SII902X_SYS_CTRL_DATA,
				 SII902X_SYS_CTRL_OUTPUT_MODE, output_mode);
	if (ret)
		goto error_out;

	ret = num;

error_out:
	mutex_unlock(&sii902x->mutex);

	return ret;
}