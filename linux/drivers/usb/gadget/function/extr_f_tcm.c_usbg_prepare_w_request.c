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
struct se_cmd {int /*<<< orphan*/  data_length; int /*<<< orphan*/  t_data_sg; int /*<<< orphan*/  t_data_nents; } ;
struct usbg_cmd {int /*<<< orphan*/ * data_buf; struct f_uas* fu; struct se_cmd se_cmd; } ;
struct usb_request {struct usbg_cmd* context; int /*<<< orphan*/  length; int /*<<< orphan*/  complete; int /*<<< orphan*/  sg; int /*<<< orphan*/  num_sgs; int /*<<< orphan*/ * buf; } ;
struct usb_gadget {int /*<<< orphan*/  sg_supported; } ;
struct f_uas {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct usb_gadget* fuas_to_gadget (struct f_uas*) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbg_data_write_cmpl ; 

__attribute__((used)) static int usbg_prepare_w_request(struct usbg_cmd *cmd, struct usb_request *req)
{
	struct se_cmd *se_cmd = &cmd->se_cmd;
	struct f_uas *fu = cmd->fu;
	struct usb_gadget *gadget = fuas_to_gadget(fu);

	if (!gadget->sg_supported) {
		cmd->data_buf = kmalloc(se_cmd->data_length, GFP_ATOMIC);
		if (!cmd->data_buf)
			return -ENOMEM;

		req->buf = cmd->data_buf;
	} else {
		req->buf = NULL;
		req->num_sgs = se_cmd->t_data_nents;
		req->sg = se_cmd->t_data_sg;
	}

	req->complete = usbg_data_write_cmpl;
	req->length = se_cmd->data_length;
	req->context = cmd;
	return 0;
}