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
struct drm_hdmi_info {int /*<<< orphan*/  y420_vdb_modes; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_2__ {struct drm_hdmi_info hdmi; } ;
struct drm_connector {int /*<<< orphan*/  ycbcr_420_allowed; TYPE_1__ display_info; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_NO_420 ; 
 int MODE_OK ; 
 int /*<<< orphan*/  drm_match_cea_mode (struct drm_display_mode const*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum drm_mode_status
drm_mode_validate_ycbcr420(const struct drm_display_mode *mode,
			   struct drm_connector *connector)
{
	u8 vic = drm_match_cea_mode(mode);
	enum drm_mode_status status = MODE_OK;
	struct drm_hdmi_info *hdmi = &connector->display_info.hdmi;

	if (test_bit(vic, hdmi->y420_vdb_modes)) {
		if (!connector->ycbcr_420_allowed)
			status = MODE_NO_420;
	}

	return status;
}