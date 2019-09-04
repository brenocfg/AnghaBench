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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__* params; } ;
struct hidpp_report {TYPE_1__ fap; } ;
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ROOT_GET_FEATURE ; 
 int ENOENT ; 
 int /*<<< orphan*/  HIDPP_PAGE_ROOT_IDX ; 
 int hidpp_send_fap_command_sync (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,struct hidpp_report*) ; 

__attribute__((used)) static int hidpp_root_get_feature(struct hidpp_device *hidpp, u16 feature,
	u8 *feature_index, u8 *feature_type)
{
	struct hidpp_report response;
	int ret;
	u8 params[2] = { feature >> 8, feature & 0x00FF };

	ret = hidpp_send_fap_command_sync(hidpp,
			HIDPP_PAGE_ROOT_IDX,
			CMD_ROOT_GET_FEATURE,
			params, 2, &response);
	if (ret)
		return ret;

	if (response.fap.params[0] == 0)
		return -ENOENT;

	*feature_index = response.fap.params[0];
	*feature_type = response.fap.params[1];

	return ret;
}