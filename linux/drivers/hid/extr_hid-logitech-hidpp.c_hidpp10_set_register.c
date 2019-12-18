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
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  params; } ;
struct hidpp_report {TYPE_1__ rap; } ;
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDPP_GET_REGISTER ; 
 int /*<<< orphan*/  HIDPP_SET_REGISTER ; 
 int /*<<< orphan*/  REPORT_ID_HIDPP_SHORT ; 
 int hidpp_send_rap_command_sync (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t*,int,struct hidpp_report*) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hidpp10_set_register(struct hidpp_device *hidpp_dev,
	u8 register_address, u8 byte, u8 mask, u8 value)
{
	struct hidpp_report response;
	int ret;
	u8 params[3] = { 0 };

	ret = hidpp_send_rap_command_sync(hidpp_dev,
					  REPORT_ID_HIDPP_SHORT,
					  HIDPP_GET_REGISTER,
					  register_address,
					  NULL, 0, &response);
	if (ret)
		return ret;

	memcpy(params, response.rap.params, 3);

	params[byte] &= ~mask;
	params[byte] |= value & mask;

	return hidpp_send_rap_command_sync(hidpp_dev,
					   REPORT_ID_HIDPP_SHORT,
					   HIDPP_SET_REGISTER,
					   register_address,
					   params, 3, &response);
}