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
typedef  void* u8 ;
struct TYPE_2__ {int /*<<< orphan*/  params; void* funcindex_clientid; void* feature_index; } ;
struct hidpp_report {TYPE_1__ fap; int /*<<< orphan*/  report_id; } ;
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIDPP_REPORT_LONG_LENGTH ; 
 int /*<<< orphan*/  REPORT_ID_HIDPP_LONG ; 
 int /*<<< orphan*/  REPORT_ID_HIDPP_VERY_LONG ; 
 int hidpp_send_message_sync (struct hidpp_device*,struct hidpp_report*,struct hidpp_report*) ; 
 int /*<<< orphan*/  kfree (struct hidpp_report*) ; 
 struct hidpp_report* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void**,int) ; 

__attribute__((used)) static int hidpp_send_fap_command_sync(struct hidpp_device *hidpp,
	u8 feat_index, u8 funcindex_clientid, u8 *params, int param_count,
	struct hidpp_report *response)
{
	struct hidpp_report *message;
	int ret;

	if (param_count > sizeof(message->fap.params))
		return -EINVAL;

	message = kzalloc(sizeof(struct hidpp_report), GFP_KERNEL);
	if (!message)
		return -ENOMEM;

	if (param_count > (HIDPP_REPORT_LONG_LENGTH - 4))
		message->report_id = REPORT_ID_HIDPP_VERY_LONG;
	else
		message->report_id = REPORT_ID_HIDPP_LONG;
	message->fap.feature_index = feat_index;
	message->fap.funcindex_clientid = funcindex_clientid;
	memcpy(&message->fap.params, params, param_count);

	ret = hidpp_send_message_sync(hidpp, message, response);
	kfree(message);
	return ret;
}