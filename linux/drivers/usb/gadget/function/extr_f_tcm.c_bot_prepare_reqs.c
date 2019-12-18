#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* req; TYPE_6__* buf; } ;
struct TYPE_12__ {int /*<<< orphan*/  Signature; } ;
struct TYPE_8__ {TYPE_4__* req; TYPE_6__ csw; } ;
struct f_uas {TYPE_4__* bot_req_in; TYPE_3__* ep_in; TYPE_4__* bot_req_out; TYPE_3__* ep_out; TYPE_2__ cmd; TYPE_1__ bot_status; } ;
struct TYPE_11__ {struct f_uas* context; int /*<<< orphan*/  length; TYPE_6__* buf; int /*<<< orphan*/  complete; } ;
struct TYPE_10__ {int /*<<< orphan*/  maxpacket; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  US_BULK_CS_SIGN ; 
 int /*<<< orphan*/  US_BULK_CS_WRAP_LEN ; 
 int /*<<< orphan*/  bot_cmd_complete ; 
 int bot_enqueue_cmd_cbw (struct f_uas*) ; 
 int /*<<< orphan*/  bot_status_complete ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_6__*) ; 
 TYPE_6__* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 void* usb_ep_alloc_request (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static int bot_prepare_reqs(struct f_uas *fu)
{
	int ret;

	fu->bot_req_in = usb_ep_alloc_request(fu->ep_in, GFP_KERNEL);
	if (!fu->bot_req_in)
		goto err;

	fu->bot_req_out = usb_ep_alloc_request(fu->ep_out, GFP_KERNEL);
	if (!fu->bot_req_out)
		goto err_out;

	fu->cmd.req = usb_ep_alloc_request(fu->ep_out, GFP_KERNEL);
	if (!fu->cmd.req)
		goto err_cmd;

	fu->bot_status.req = usb_ep_alloc_request(fu->ep_in, GFP_KERNEL);
	if (!fu->bot_status.req)
		goto err_sts;

	fu->bot_status.req->buf = &fu->bot_status.csw;
	fu->bot_status.req->length = US_BULK_CS_WRAP_LEN;
	fu->bot_status.req->complete = bot_status_complete;
	fu->bot_status.csw.Signature = cpu_to_le32(US_BULK_CS_SIGN);

	fu->cmd.buf = kmalloc(fu->ep_out->maxpacket, GFP_KERNEL);
	if (!fu->cmd.buf)
		goto err_buf;

	fu->cmd.req->complete = bot_cmd_complete;
	fu->cmd.req->buf = fu->cmd.buf;
	fu->cmd.req->length = fu->ep_out->maxpacket;
	fu->cmd.req->context = fu;

	ret = bot_enqueue_cmd_cbw(fu);
	if (ret)
		goto err_queue;
	return 0;
err_queue:
	kfree(fu->cmd.buf);
	fu->cmd.buf = NULL;
err_buf:
	usb_ep_free_request(fu->ep_in, fu->bot_status.req);
err_sts:
	usb_ep_free_request(fu->ep_out, fu->cmd.req);
	fu->cmd.req = NULL;
err_cmd:
	usb_ep_free_request(fu->ep_out, fu->bot_req_out);
	fu->bot_req_out = NULL;
err_out:
	usb_ep_free_request(fu->ep_in, fu->bot_req_in);
	fu->bot_req_in = NULL;
err:
	pr_err("BOT: endpoint setup failed\n");
	return -ENOMEM;
}