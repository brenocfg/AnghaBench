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
struct hidpp_device {int /*<<< orphan*/  hid_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDPP_PAGE_G920_FORCE_FEEDBACK ; 
 int /*<<< orphan*/  hid_warn (int /*<<< orphan*/ ,char*,int) ; 
 int hidpp_ff_init (struct hidpp_device*,int /*<<< orphan*/ ) ; 
 int hidpp_root_get_feature (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g920_get_config(struct hidpp_device *hidpp)
{
	u8 feature_type;
	u8 feature_index;
	int ret;

	/* Find feature and store for later use */
	ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_G920_FORCE_FEEDBACK,
		&feature_index, &feature_type);
	if (ret)
		return ret;

	ret = hidpp_ff_init(hidpp, feature_index);
	if (ret)
		hid_warn(hidpp->hid_dev, "Unable to initialize force feedback support, errno %d\n",
				ret);

	return 0;
}