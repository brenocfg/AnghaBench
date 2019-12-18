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
struct usbhsh_request {int /*<<< orphan*/  pkt; } ;
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_pipe {int /*<<< orphan*/ * handler; } ;
struct urb {int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  pipe; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_dcp_status_stage_in_handler ; 
 int /*<<< orphan*/  usbhs_dcp_status_stage_out_handler ; 
 int /*<<< orphan*/  usbhs_pkt_push (struct usbhs_pipe*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbhsh_queue_done ; 
 struct usbhsh_request* usbhsh_ureq_alloc (struct usbhsh_hpriv*,struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsh_status_stage_packet_push(struct usbhsh_hpriv *hpriv,
					    struct urb *urb,
					    struct usbhs_pipe *pipe,
					    gfp_t mem_flags)
{
	struct usbhsh_request *ureq;

	/* This ureq will be freed on usbhsh_queue_done() */
	ureq = usbhsh_ureq_alloc(hpriv, urb, mem_flags);
	if (unlikely(!ureq))
		return -ENOMEM;

	if (usb_pipein(urb->pipe))
		pipe->handler = &usbhs_dcp_status_stage_in_handler;
	else
		pipe->handler = &usbhs_dcp_status_stage_out_handler;

	usbhs_pkt_push(pipe, &ureq->pkt,
		       usbhsh_queue_done,
		       NULL,
		       urb->transfer_buffer_length,
		       0, -1);

	return 0;
}