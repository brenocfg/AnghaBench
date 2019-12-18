#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  controller; int /*<<< orphan*/ * dev; } ;
struct smscore_device_t {int gfp_buf_flags; int /*<<< orphan*/  ir_init_done; TYPE_2__ ir; } ;
struct TYPE_8__ {int /*<<< orphan*/  msg_length; } ;
struct sms_msg_data2 {TYPE_4__ x_msg_header; int /*<<< orphan*/ * msg_data; } ;
struct TYPE_5__ {int ir; } ;
struct TYPE_7__ {TYPE_1__ board_cfg; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_SMS_START_IR_REQ ; 
 scalar_t__ SMS_ALIGN_ADDRESS (void*) ; 
 scalar_t__ SMS_DMA_ALIGNMENT ; 
 int /*<<< orphan*/  SMS_INIT_MSG (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 TYPE_3__* sms_get_board (int /*<<< orphan*/ ) ; 
 int sms_ir_init (struct smscore_device_t*) ; 
 int /*<<< orphan*/  smscore_get_board_id (struct smscore_device_t*) ; 
 int smscore_sendrequest_and_wait (struct smscore_device_t*,struct sms_msg_data2*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smscore_init_ir(struct smscore_device_t *coredev)
{
	int ir_io;
	int rc;
	void *buffer;

	coredev->ir.dev = NULL;
	ir_io = sms_get_board(smscore_get_board_id(coredev))->board_cfg.ir;
	if (ir_io) {/* only if IR port exist we use IR sub-module */
		pr_debug("IR loading\n");
		rc = sms_ir_init(coredev);

		if	(rc != 0)
			pr_err("Error initialization DTV IR sub-module\n");
		else {
			buffer = kmalloc(sizeof(struct sms_msg_data2) +
						SMS_DMA_ALIGNMENT,
						GFP_KERNEL | coredev->gfp_buf_flags);
			if (buffer) {
				struct sms_msg_data2 *msg =
				(struct sms_msg_data2 *)
				SMS_ALIGN_ADDRESS(buffer);

				SMS_INIT_MSG(&msg->x_msg_header,
						MSG_SMS_START_IR_REQ,
						sizeof(struct sms_msg_data2));
				msg->msg_data[0] = coredev->ir.controller;
				msg->msg_data[1] = coredev->ir.timeout;

				rc = smscore_sendrequest_and_wait(coredev, msg,
						msg->x_msg_header. msg_length,
						&coredev->ir_init_done);

				kfree(buffer);
			} else
				pr_err("Sending IR initialization message failed\n");
		}
	} else
		pr_info("IR port has not been detected\n");

	return 0;
}