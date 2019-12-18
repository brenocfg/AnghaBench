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
struct smscore_device_t {int gfp_buf_flags; int /*<<< orphan*/  init_device_done; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_length; } ;
struct sms_msg_data {int* msg_data; TYPE_1__ x_msg_header; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_SMS_INIT_DEVICE_REQ ; 
 scalar_t__ SMS_ALIGN_ADDRESS (void*) ; 
 scalar_t__ SMS_DMA_ALIGNMENT ; 
 int /*<<< orphan*/  SMS_INIT_MSG (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (scalar_t__,int) ; 
 int smscore_sendrequest_and_wait (struct smscore_device_t*,struct sms_msg_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smscore_init_device(struct smscore_device_t *coredev, int mode)
{
	void *buffer;
	struct sms_msg_data *msg;
	int rc = 0;

	buffer = kmalloc(sizeof(struct sms_msg_data) +
			SMS_DMA_ALIGNMENT, GFP_KERNEL | coredev->gfp_buf_flags);
	if (!buffer)
		return -ENOMEM;

	msg = (struct sms_msg_data *)SMS_ALIGN_ADDRESS(buffer);
	SMS_INIT_MSG(&msg->x_msg_header, MSG_SMS_INIT_DEVICE_REQ,
			sizeof(struct sms_msg_data));
	msg->msg_data[0] = mode;

	rc = smscore_sendrequest_and_wait(coredev, msg,
			msg->x_msg_header. msg_length,
			&coredev->init_device_done);

	kfree(buffer);
	return rc;
}