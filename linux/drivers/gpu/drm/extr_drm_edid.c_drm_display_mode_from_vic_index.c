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
typedef  size_t u8 ;
struct drm_display_mode {scalar_t__ vrefresh; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_valid_cea_vic (size_t) ; 
 int /*<<< orphan*/ * edid_cea_modes ; 
 size_t svd_to_vic (size_t const) ; 

__attribute__((used)) static struct drm_display_mode *
drm_display_mode_from_vic_index(struct drm_connector *connector,
				const u8 *video_db, u8 video_len,
				u8 video_index)
{
	struct drm_device *dev = connector->dev;
	struct drm_display_mode *newmode;
	u8 vic;

	if (video_db == NULL || video_index >= video_len)
		return NULL;

	/* CEA modes are numbered 1..127 */
	vic = svd_to_vic(video_db[video_index]);
	if (!drm_valid_cea_vic(vic))
		return NULL;

	newmode = drm_mode_duplicate(dev, &edid_cea_modes[vic]);
	if (!newmode)
		return NULL;

	newmode->vrefresh = 0;

	return newmode;
}