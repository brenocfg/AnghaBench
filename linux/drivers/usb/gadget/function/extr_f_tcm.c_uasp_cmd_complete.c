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
struct usb_request {scalar_t__ status; int /*<<< orphan*/  actual; int /*<<< orphan*/  buf; struct f_uas* context; } ;
struct usb_ep {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  req; } ;
struct f_uas {TYPE_1__ cmd; int /*<<< orphan*/  ep_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  usb_ep_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbg_submit_command (struct f_uas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uasp_cmd_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct f_uas *fu = req->context;
	int ret;

	if (req->status < 0)
		return;

	ret = usbg_submit_command(fu, req->buf, req->actual);
	/*
	 * Once we tune for performance enqueue the command req here again so
	 * we can receive a second command while we processing this one. Pay
	 * attention to properly sync STAUS endpoint with DATA IN + OUT so you
	 * don't break HS.
	 */
	if (!ret)
		return;
	usb_ep_queue(fu->ep_cmd, fu->cmd.req, GFP_ATOMIC);
}