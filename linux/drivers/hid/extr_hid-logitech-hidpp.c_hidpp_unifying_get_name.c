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
struct TYPE_2__ {int* params; } ;
struct hidpp_report {TYPE_1__ rap; } ;
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIDPP_DEVICE_NAME ; 
 int /*<<< orphan*/  HIDPP_GET_LONG_REGISTER ; 
 int /*<<< orphan*/  HIDPP_REG_PAIRING_INFORMATION ; 
 int /*<<< orphan*/  REPORT_ID_HIDPP_SHORT ; 
 int /*<<< orphan*/  hidpp_prefix_name (char**,int) ; 
 int hidpp_send_rap_command_sync (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct hidpp_report*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 

__attribute__((used)) static char *hidpp_unifying_get_name(struct hidpp_device *hidpp_dev)
{
	struct hidpp_report response;
	int ret;
	u8 params[1] = { HIDPP_DEVICE_NAME };
	char *name;
	int len;

	ret = hidpp_send_rap_command_sync(hidpp_dev,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_GET_LONG_REGISTER,
					HIDPP_REG_PAIRING_INFORMATION,
					params, 1, &response);
	if (ret)
		return NULL;

	len = response.rap.params[1];

	if (2 + len > sizeof(response.rap.params))
		return NULL;

	if (len < 4) /* logitech devices are usually at least Xddd */
		return NULL;

	name = kzalloc(len + 1, GFP_KERNEL);
	if (!name)
		return NULL;

	memcpy(name, &response.rap.params[2], len);

	/* include the terminating '\0' */
	hidpp_prefix_name(&name, len + 1);

	return name;
}