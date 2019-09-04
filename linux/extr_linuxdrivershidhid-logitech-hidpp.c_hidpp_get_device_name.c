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
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIDPP_PAGE_GET_DEVICE_NAME_TYPE ; 
 int hidpp_devicenametype_get_count (struct hidpp_device*,int,int*) ; 
 int hidpp_devicenametype_get_device_name (struct hidpp_device*,int,unsigned int,char*,int) ; 
 int /*<<< orphan*/  hidpp_prefix_name (char**,int) ; 
 int hidpp_root_get_feature (struct hidpp_device*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *hidpp_get_device_name(struct hidpp_device *hidpp)
{
	u8 feature_type;
	u8 feature_index;
	u8 __name_length;
	char *name;
	unsigned index = 0;
	int ret;

	ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_GET_DEVICE_NAME_TYPE,
		&feature_index, &feature_type);
	if (ret)
		return NULL;

	ret = hidpp_devicenametype_get_count(hidpp, feature_index,
		&__name_length);
	if (ret)
		return NULL;

	name = kzalloc(__name_length + 1, GFP_KERNEL);
	if (!name)
		return NULL;

	while (index < __name_length) {
		ret = hidpp_devicenametype_get_device_name(hidpp,
			feature_index, index, name + index,
			__name_length - index);
		if (ret <= 0) {
			kfree(name);
			return NULL;
		}
		index += ret;
	}

	/* include the terminating '\0' */
	hidpp_prefix_name(&name, __name_length + 1);

	return name;
}