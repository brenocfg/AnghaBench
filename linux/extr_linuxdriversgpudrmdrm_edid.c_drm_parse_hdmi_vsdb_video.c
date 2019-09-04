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
struct drm_display_info {int dvi_dual; int max_tmds_clock; } ;
struct drm_connector {struct drm_display_info display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int cea_db_payload_len (int const*) ; 
 int /*<<< orphan*/  drm_parse_hdmi_deep_color_info (struct drm_connector*,int const*) ; 

__attribute__((used)) static void
drm_parse_hdmi_vsdb_video(struct drm_connector *connector, const u8 *db)
{
	struct drm_display_info *info = &connector->display_info;
	u8 len = cea_db_payload_len(db);

	if (len >= 6)
		info->dvi_dual = db[6] & 1;
	if (len >= 7)
		info->max_tmds_clock = db[7] * 5000;

	DRM_DEBUG_KMS("HDMI: DVI dual %d, "
		      "max TMDS clock %d kHz\n",
		      info->dvi_dual,
		      info->max_tmds_clock);

	drm_parse_hdmi_deep_color_info(connector, db);
}