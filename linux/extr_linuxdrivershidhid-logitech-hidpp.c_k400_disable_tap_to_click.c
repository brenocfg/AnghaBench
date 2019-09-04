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
struct k400_private_data {int /*<<< orphan*/  feature_index; } ;
struct hidpp_touchpad_fw_items {int dummy; } ;
struct hidpp_device {struct k400_private_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDPP_PAGE_TOUCHPAD_FW_ITEMS ; 
 int hidpp_root_get_feature (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hidpp_touchpad_fw_items_set (struct hidpp_device*,int /*<<< orphan*/ ,struct hidpp_touchpad_fw_items*) ; 

__attribute__((used)) static int k400_disable_tap_to_click(struct hidpp_device *hidpp)
{
	struct k400_private_data *k400 = hidpp->private_data;
	struct hidpp_touchpad_fw_items items = {};
	int ret;
	u8 feature_type;

	if (!k400->feature_index) {
		ret = hidpp_root_get_feature(hidpp,
			HIDPP_PAGE_TOUCHPAD_FW_ITEMS,
			&k400->feature_index, &feature_type);
		if (ret)
			/* means that the device is not powered up */
			return ret;
	}

	ret = hidpp_touchpad_fw_items_set(hidpp, k400->feature_index, &items);
	if (ret)
		return ret;

	return 0;
}