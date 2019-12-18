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
struct drm_display_mode {unsigned int flags; } ;
struct drm_display_info {int has_hdmi_infoframe; } ;
struct drm_connector {struct drm_display_info display_info; } ;

/* Variables and functions */
 unsigned int DRM_MODE_FLAG_3D_FRAME_PACKING ; 
 unsigned int DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF ; 
 unsigned int DRM_MODE_FLAG_3D_TOP_AND_BOTTOM ; 
 scalar_t__ add_3d_struct_modes (struct drm_connector*,int,int const*,int,int) ; 
 scalar_t__ add_hdmi_mandatory_stereo_modes (struct drm_connector*) ; 
 scalar_t__ add_hdmi_mode (struct drm_connector*,int) ; 
 struct drm_display_mode* drm_display_mode_from_vic_index (struct drm_connector*,int const*,int,int) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 

__attribute__((used)) static int
do_hdmi_vsdb_modes(struct drm_connector *connector, const u8 *db, u8 len,
		   const u8 *video_db, u8 video_len)
{
	struct drm_display_info *info = &connector->display_info;
	int modes = 0, offset = 0, i, multi_present = 0, multi_len;
	u8 vic_len, hdmi_3d_len = 0;
	u16 mask;
	u16 structure_all;

	if (len < 8)
		goto out;

	/* no HDMI_Video_Present */
	if (!(db[8] & (1 << 5)))
		goto out;

	/* Latency_Fields_Present */
	if (db[8] & (1 << 7))
		offset += 2;

	/* I_Latency_Fields_Present */
	if (db[8] & (1 << 6))
		offset += 2;

	/* the declared length is not long enough for the 2 first bytes
	 * of additional video format capabilities */
	if (len < (8 + offset + 2))
		goto out;

	/* 3D_Present */
	offset++;
	if (db[8 + offset] & (1 << 7)) {
		modes += add_hdmi_mandatory_stereo_modes(connector);

		/* 3D_Multi_present */
		multi_present = (db[8 + offset] & 0x60) >> 5;
	}

	offset++;
	vic_len = db[8 + offset] >> 5;
	hdmi_3d_len = db[8 + offset] & 0x1f;

	for (i = 0; i < vic_len && len >= (9 + offset + i); i++) {
		u8 vic;

		vic = db[9 + offset + i];
		modes += add_hdmi_mode(connector, vic);
	}
	offset += 1 + vic_len;

	if (multi_present == 1)
		multi_len = 2;
	else if (multi_present == 2)
		multi_len = 4;
	else
		multi_len = 0;

	if (len < (8 + offset + hdmi_3d_len - 1))
		goto out;

	if (hdmi_3d_len < multi_len)
		goto out;

	if (multi_present == 1 || multi_present == 2) {
		/* 3D_Structure_ALL */
		structure_all = (db[8 + offset] << 8) | db[9 + offset];

		/* check if 3D_MASK is present */
		if (multi_present == 2)
			mask = (db[10 + offset] << 8) | db[11 + offset];
		else
			mask = 0xffff;

		for (i = 0; i < 16; i++) {
			if (mask & (1 << i))
				modes += add_3d_struct_modes(connector,
						structure_all,
						video_db,
						video_len, i);
		}
	}

	offset += multi_len;

	for (i = 0; i < (hdmi_3d_len - multi_len); i++) {
		int vic_index;
		struct drm_display_mode *newmode = NULL;
		unsigned int newflag = 0;
		bool detail_present;

		detail_present = ((db[8 + offset + i] & 0x0f) > 7);

		if (detail_present && (i + 1 == hdmi_3d_len - multi_len))
			break;

		/* 2D_VIC_order_X */
		vic_index = db[8 + offset + i] >> 4;

		/* 3D_Structure_X */
		switch (db[8 + offset + i] & 0x0f) {
		case 0:
			newflag = DRM_MODE_FLAG_3D_FRAME_PACKING;
			break;
		case 6:
			newflag = DRM_MODE_FLAG_3D_TOP_AND_BOTTOM;
			break;
		case 8:
			/* 3D_Detail_X */
			if ((db[9 + offset + i] >> 4) == 1)
				newflag = DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF;
			break;
		}

		if (newflag != 0) {
			newmode = drm_display_mode_from_vic_index(connector,
								  video_db,
								  video_len,
								  vic_index);

			if (newmode) {
				newmode->flags |= newflag;
				drm_mode_probed_add(connector, newmode);
				modes++;
			}
		}

		if (detail_present)
			i++;
	}

out:
	if (modes > 0)
		info->has_hdmi_infoframe = true;
	return modes;
}