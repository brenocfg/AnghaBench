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
struct usbhs_pkt {int /*<<< orphan*/  length; int /*<<< orphan*/  actual; int /*<<< orphan*/ * handler; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhs_dcp_status_stage_in_handler ; 
 int /*<<< orphan*/  usbhsf_rx_irq_ctrl (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_tx_irq_ctrl (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhs_dcp_dir_switch_done(struct usbhs_pkt *pkt, int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;

	if (pkt->handler == &usbhs_dcp_status_stage_in_handler)
		usbhsf_tx_irq_ctrl(pipe, 0);
	else
		usbhsf_rx_irq_ctrl(pipe, 0);

	pkt->actual = pkt->length;
	*is_done = 1;

	return 0;
}