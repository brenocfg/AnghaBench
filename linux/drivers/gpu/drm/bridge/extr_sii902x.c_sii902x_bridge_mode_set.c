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
typedef  int u16 ;
struct sii902x {int /*<<< orphan*/  mutex; int /*<<< orphan*/  connector; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct hdmi_avi_infoframe {int dummy; } ;
struct drm_display_mode {int clock; int vrefresh; int hdisplay; int vdisplay; } ;
struct drm_bridge {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AVI ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int HDMI_AVI_INFOFRAME_SIZE ; 
 int HDMI_INFOFRAME_HEADER_SIZE ; 
 int HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SII902X_TPI_AVI_INFOFRAME ; 
 int SII902X_TPI_AVI_INPUT_COLORSPACE_RGB ; 
 int SII902X_TPI_AVI_INPUT_RANGE_AUTO ; 
 int SII902X_TPI_AVI_PIXEL_REP_BUS_24BIT ; 
 int SII902X_TPI_AVI_PIXEL_REP_NONE ; 
 int SII902X_TPI_CLK_RATIO_1X ; 
 int /*<<< orphan*/  SII902X_TPI_VIDEO_DATA ; 
 struct sii902x* bridge_to_sii902x (struct drm_bridge*) ; 
 int drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,struct drm_display_mode const*) ; 
 int hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_write (struct regmap*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sii902x_bridge_mode_set(struct drm_bridge *bridge,
				    const struct drm_display_mode *mode,
				    const struct drm_display_mode *adj)
{
	struct sii902x *sii902x = bridge_to_sii902x(bridge);
	struct regmap *regmap = sii902x->regmap;
	u8 buf[HDMI_INFOFRAME_SIZE(AVI)];
	struct hdmi_avi_infoframe frame;
	u16 pixel_clock_10kHz = adj->clock / 10;
	int ret;

	buf[0] = pixel_clock_10kHz & 0xff;
	buf[1] = pixel_clock_10kHz >> 8;
	buf[2] = adj->vrefresh;
	buf[3] = 0x00;
	buf[4] = adj->hdisplay;
	buf[5] = adj->hdisplay >> 8;
	buf[6] = adj->vdisplay;
	buf[7] = adj->vdisplay >> 8;
	buf[8] = SII902X_TPI_CLK_RATIO_1X | SII902X_TPI_AVI_PIXEL_REP_NONE |
		 SII902X_TPI_AVI_PIXEL_REP_BUS_24BIT;
	buf[9] = SII902X_TPI_AVI_INPUT_RANGE_AUTO |
		 SII902X_TPI_AVI_INPUT_COLORSPACE_RGB;

	mutex_lock(&sii902x->mutex);

	ret = regmap_bulk_write(regmap, SII902X_TPI_VIDEO_DATA, buf, 10);
	if (ret)
		goto out;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &sii902x->connector, adj);
	if (ret < 0) {
		DRM_ERROR("couldn't fill AVI infoframe\n");
		goto out;
	}

	ret = hdmi_avi_infoframe_pack(&frame, buf, sizeof(buf));
	if (ret < 0) {
		DRM_ERROR("failed to pack AVI infoframe: %d\n", ret);
		goto out;
	}

	/* Do not send the infoframe header, but keep the CRC field. */
	regmap_bulk_write(regmap, SII902X_TPI_AVI_INFOFRAME,
			  buf + HDMI_INFOFRAME_HEADER_SIZE - 1,
			  HDMI_AVI_INFOFRAME_SIZE + 1);

out:
	mutex_unlock(&sii902x->mutex);
}