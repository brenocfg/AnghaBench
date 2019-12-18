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
struct us_data {unsigned int recv_intr_pipe; TYPE_1__* current_urb; int /*<<< orphan*/  ep_bInterval; int /*<<< orphan*/  pusb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  actual_length; } ;

/* Variables and functions */
 int interpret_urb_result (struct us_data*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,void*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int usb_maxpacket (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeout (unsigned int) ; 
 int /*<<< orphan*/  usb_stor_blocking_completion ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,unsigned int) ; 
 int usb_stor_msg_common (struct us_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_stor_intr_transfer(struct us_data *us, void *buf,
				  unsigned int length)
{
	int result;
	unsigned int pipe = us->recv_intr_pipe;
	unsigned int maxp;

	usb_stor_dbg(us, "xfer %u bytes\n", length);

	/* calculate the max packet size */
	maxp = usb_maxpacket(us->pusb_dev, pipe, usb_pipeout(pipe));
	if (maxp > length)
		maxp = length;

	/* fill and submit the URB */
	usb_fill_int_urb(us->current_urb, us->pusb_dev, pipe, buf,
			maxp, usb_stor_blocking_completion, NULL,
			us->ep_bInterval);
	result = usb_stor_msg_common(us, 0);

	return interpret_urb_result(us, pipe, length, result,
			us->current_urb->actual_length);
}