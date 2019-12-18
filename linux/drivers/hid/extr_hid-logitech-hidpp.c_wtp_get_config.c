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
typedef  int /*<<< orphan*/  u8 ;
struct wtp_data {int flip_y; scalar_t__ resolution; int /*<<< orphan*/  maxcontacts; int /*<<< orphan*/  y_size; int /*<<< orphan*/  x_size; int /*<<< orphan*/  mt_feature_index; } ;
struct hidpp_touchpad_raw_info {scalar_t__ origin; scalar_t__ res; int /*<<< orphan*/  maxcontacts; int /*<<< orphan*/  y_size; int /*<<< orphan*/  x_size; int /*<<< orphan*/  member_0; } ;
struct hidpp_device {struct wtp_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDPP_PAGE_TOUCHPAD_RAW_XY ; 
 scalar_t__ TOUCHPAD_RAW_XY_ORIGIN_LOWER_LEFT ; 
 scalar_t__ WTP_MANUAL_RESOLUTION ; 
 int hidpp_root_get_feature (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hidpp_touchpad_get_raw_info (struct hidpp_device*,int /*<<< orphan*/ ,struct hidpp_touchpad_raw_info*) ; 

__attribute__((used)) static int wtp_get_config(struct hidpp_device *hidpp)
{
	struct wtp_data *wd = hidpp->private_data;
	struct hidpp_touchpad_raw_info raw_info = {0};
	u8 feature_type;
	int ret;

	ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_TOUCHPAD_RAW_XY,
		&wd->mt_feature_index, &feature_type);
	if (ret)
		/* means that the device is not powered up */
		return ret;

	ret = hidpp_touchpad_get_raw_info(hidpp, wd->mt_feature_index,
		&raw_info);
	if (ret)
		return ret;

	wd->x_size = raw_info.x_size;
	wd->y_size = raw_info.y_size;
	wd->maxcontacts = raw_info.maxcontacts;
	wd->flip_y = raw_info.origin == TOUCHPAD_RAW_XY_ORIGIN_LOWER_LEFT;
	wd->resolution = raw_info.res;
	if (!wd->resolution)
		wd->resolution = WTP_MANUAL_RESOLUTION;

	return 0;
}