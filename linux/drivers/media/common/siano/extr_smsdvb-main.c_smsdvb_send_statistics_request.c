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
struct smsdvb_client_t {int /*<<< orphan*/  stats_done; TYPE_1__* coredev; scalar_t__ get_stats_jiffies; } ;
struct sms_msg_hdr {int msg_length; void* msg_type; scalar_t__ msg_flags; int /*<<< orphan*/  msg_dst_id; int /*<<< orphan*/  msg_src_id; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int fw_version; } ;

/* Variables and functions */
#define  DEVICE_MODE_ISDBT 129 
#define  DEVICE_MODE_ISDBT_BDA 128 
 int /*<<< orphan*/  DVBT_BDA_CONTROL_MSG_ID ; 
 int /*<<< orphan*/  HIF_TASK ; 
 void* MSG_SMS_GET_STATISTICS_EX_REQ ; 
 void* MSG_SMS_GET_STATISTICS_REQ ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int smscore_get_device_mode (TYPE_1__*) ; 
 int smsdvb_sendrequest_and_wait (struct smsdvb_client_t*,struct sms_msg_hdr*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int smsdvb_send_statistics_request(struct smsdvb_client_t *client)
{
	int rc;
	struct sms_msg_hdr msg;

	/* Don't request stats too fast */
	if (client->get_stats_jiffies &&
	   (!time_after(jiffies, client->get_stats_jiffies)))
		return 0;
	client->get_stats_jiffies = jiffies + msecs_to_jiffies(100);

	msg.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	msg.msg_dst_id = HIF_TASK;
	msg.msg_flags = 0;
	msg.msg_length = sizeof(msg);

	switch (smscore_get_device_mode(client->coredev)) {
	case DEVICE_MODE_ISDBT:
	case DEVICE_MODE_ISDBT_BDA:
		/*
		* Check for firmware version, to avoid breaking for old cards
		*/
		if (client->coredev->fw_version >= 0x800)
			msg.msg_type = MSG_SMS_GET_STATISTICS_EX_REQ;
		else
			msg.msg_type = MSG_SMS_GET_STATISTICS_REQ;
		break;
	default:
		msg.msg_type = MSG_SMS_GET_STATISTICS_REQ;
	}

	rc = smsdvb_sendrequest_and_wait(client, &msg, sizeof(msg),
					 &client->stats_done);

	return rc;
}