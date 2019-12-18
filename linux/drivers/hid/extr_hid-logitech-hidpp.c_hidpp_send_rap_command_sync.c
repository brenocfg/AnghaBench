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
struct TYPE_2__ {int sub_id; int reg_address; int /*<<< orphan*/  params; } ;
struct hidpp_report {int report_id; TYPE_1__ rap; } ;
struct hidpp_device {int /*<<< orphan*/  very_long_report_length; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIDPP_REPORT_LONG_LENGTH ; 
 int /*<<< orphan*/  HIDPP_REPORT_SHORT_LENGTH ; 
#define  REPORT_ID_HIDPP_LONG 130 
#define  REPORT_ID_HIDPP_SHORT 129 
#define  REPORT_ID_HIDPP_VERY_LONG 128 
 int hidpp_send_message_sync (struct hidpp_device*,struct hidpp_report*,struct hidpp_report*) ; 
 int /*<<< orphan*/  kfree (struct hidpp_report*) ; 
 struct hidpp_report* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int hidpp_send_rap_command_sync(struct hidpp_device *hidpp_dev,
	u8 report_id, u8 sub_id, u8 reg_address, u8 *params, int param_count,
	struct hidpp_report *response)
{
	struct hidpp_report *message;
	int ret, max_count;

	switch (report_id) {
	case REPORT_ID_HIDPP_SHORT:
		max_count = HIDPP_REPORT_SHORT_LENGTH - 4;
		break;
	case REPORT_ID_HIDPP_LONG:
		max_count = HIDPP_REPORT_LONG_LENGTH - 4;
		break;
	case REPORT_ID_HIDPP_VERY_LONG:
		max_count = hidpp_dev->very_long_report_length - 4;
		break;
	default:
		return -EINVAL;
	}

	if (param_count > max_count)
		return -EINVAL;

	message = kzalloc(sizeof(struct hidpp_report), GFP_KERNEL);
	if (!message)
		return -ENOMEM;
	message->report_id = report_id;
	message->rap.sub_id = sub_id;
	message->rap.reg_address = reg_address;
	memcpy(&message->rap.params, params, param_count);

	ret = hidpp_send_message_sync(hidpp_dev, message, response);
	kfree(message);
	return ret;
}