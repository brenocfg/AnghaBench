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
struct dwc2_qtd {scalar_t__ in_process; scalar_t__ isoc_split_offset; int /*<<< orphan*/  isoc_split_pos; scalar_t__ complete_split; int /*<<< orphan*/  control_phase; int /*<<< orphan*/  data_toggle; struct dwc2_hcd_urb* urb; } ;
struct dwc2_hcd_urb {struct dwc2_qtd* qtd; int /*<<< orphan*/  pipe_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_CONTROL_SETUP ; 
 int /*<<< orphan*/  DWC2_HCSPLT_XACTPOS_ALL ; 
 int /*<<< orphan*/  DWC2_HC_PID_DATA1 ; 
 scalar_t__ USB_ENDPOINT_XFER_CONTROL ; 
 scalar_t__ dwc2_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 

void dwc2_hcd_qtd_init(struct dwc2_qtd *qtd, struct dwc2_hcd_urb *urb)
{
	qtd->urb = urb;
	if (dwc2_hcd_get_pipe_type(&urb->pipe_info) ==
			USB_ENDPOINT_XFER_CONTROL) {
		/*
		 * The only time the QTD data toggle is used is on the data
		 * phase of control transfers. This phase always starts with
		 * DATA1.
		 */
		qtd->data_toggle = DWC2_HC_PID_DATA1;
		qtd->control_phase = DWC2_CONTROL_SETUP;
	}

	/* Start split */
	qtd->complete_split = 0;
	qtd->isoc_split_pos = DWC2_HCSPLT_XACTPOS_ALL;
	qtd->isoc_split_offset = 0;
	qtd->in_process = 0;

	/* Store the qtd ptr in the urb to reference the QTD */
	urb->qtd = qtd;
}