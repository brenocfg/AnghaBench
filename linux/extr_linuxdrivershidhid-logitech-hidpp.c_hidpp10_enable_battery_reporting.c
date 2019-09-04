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
struct TYPE_2__ {int /*<<< orphan*/  params; } ;
struct hidpp_report {TYPE_1__ rap; } ;
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  HIDPP_GET_REGISTER ; 
 int /*<<< orphan*/  HIDPP_REG_GENERAL ; 
 int /*<<< orphan*/  HIDPP_SET_REGISTER ; 
 int /*<<< orphan*/  REPORT_ID_HIDPP_SHORT ; 
 int hidpp_send_rap_command_sync (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct hidpp_report*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hidpp10_enable_battery_reporting(struct hidpp_device *hidpp_dev)
{
	struct hidpp_report response;
	int ret;
	u8 params[3] = { 0 };

	ret = hidpp_send_rap_command_sync(hidpp_dev,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_GET_REGISTER,
					HIDPP_REG_GENERAL,
					NULL, 0, &response);
	if (ret)
		return ret;

	memcpy(params, response.rap.params, 3);

	/* Set the battery bit */
	params[0] |= BIT(4);

	return hidpp_send_rap_command_sync(hidpp_dev,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_SET_REGISTER,
					HIDPP_REG_GENERAL,
					params, 3, &response);
}