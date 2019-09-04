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
struct sms_msg_hdr {int member_3; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int DEVICE_MODE_DVBT ; 
 int DEVICE_MODE_DVBT_BDA ; 
 int EINVAL ; 
 int /*<<< orphan*/  HIF_TASK ; 
 int /*<<< orphan*/  MSG_SW_RELOAD_REQ ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int smsusb_sendrequest (void*,struct sms_msg_hdr*,int) ; 

__attribute__((used)) static int smsusb1_setmode(void *context, int mode)
{
	struct sms_msg_hdr msg = { MSG_SW_RELOAD_REQ, 0, HIF_TASK,
			     sizeof(struct sms_msg_hdr), 0 };

	if (mode < DEVICE_MODE_DVBT || mode > DEVICE_MODE_DVBT_BDA) {
		pr_err("invalid firmware id specified %d\n", mode);
		return -EINVAL;
	}

	return smsusb_sendrequest(context, &msg, sizeof(msg));
}