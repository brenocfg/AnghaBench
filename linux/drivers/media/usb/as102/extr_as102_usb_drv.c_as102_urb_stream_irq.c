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
struct urb {int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  actual_length; struct as102_dev_t* context; } ;
struct as102_dev_t {scalar_t__ streaming; int /*<<< orphan*/  dvb_dmx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS102_USB_BUF_SIZE ; 
 int /*<<< orphan*/  as102_submit_urb_stream (struct as102_dev_t*,struct urb*) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void as102_urb_stream_irq(struct urb *urb)
{
	struct as102_dev_t *as102_dev = urb->context;

	if (urb->actual_length > 0) {
		dvb_dmx_swfilter(&as102_dev->dvb_dmx,
				 urb->transfer_buffer,
				 urb->actual_length);
	} else {
		if (urb->actual_length == 0)
			memset(urb->transfer_buffer, 0, AS102_USB_BUF_SIZE);
	}

	/* is not stopped, re-submit urb */
	if (as102_dev->streaming)
		as102_submit_urb_stream(as102_dev, urb);
}