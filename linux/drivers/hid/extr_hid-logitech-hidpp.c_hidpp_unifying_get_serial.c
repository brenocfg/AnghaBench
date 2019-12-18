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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * params; } ;
struct hidpp_report {TYPE_1__ rap; } ;
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDPP_EXTENDED_PAIRING ; 
 int /*<<< orphan*/  HIDPP_GET_LONG_REGISTER ; 
 int /*<<< orphan*/  HIDPP_REG_PAIRING_INFORMATION ; 
 int /*<<< orphan*/  REPORT_ID_HIDPP_SHORT ; 
 int hidpp_send_rap_command_sync (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct hidpp_report*) ; 

__attribute__((used)) static int hidpp_unifying_get_serial(struct hidpp_device *hidpp, u32 *serial)
{
	struct hidpp_report response;
	int ret;
	u8 params[1] = { HIDPP_EXTENDED_PAIRING };

	ret = hidpp_send_rap_command_sync(hidpp,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_GET_LONG_REGISTER,
					HIDPP_REG_PAIRING_INFORMATION,
					params, 1, &response);
	if (ret)
		return ret;

	/*
	 * We don't care about LE or BE, we will output it as a string
	 * with %4phD, so we need to keep the order.
	 */
	*serial = *((u32 *)&response.rap.params[1]);
	return 0;
}