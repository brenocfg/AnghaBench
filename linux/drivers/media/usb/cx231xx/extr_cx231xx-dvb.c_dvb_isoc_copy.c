#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int status; int number_of_packets; TYPE_2__* iso_frame_desc; scalar_t__ transfer_buffer; } ;
struct cx231xx {int state; TYPE_1__* dvb; } ;
struct TYPE_4__ {int status; int /*<<< orphan*/  actual_length; scalar_t__ offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  demux; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int ENOENT ; 
 int EPROTO ; 
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_err_status (struct cx231xx*,int,int) ; 

__attribute__((used)) static inline int dvb_isoc_copy(struct cx231xx *dev, struct urb *urb)
{
	int i;

	if (!dev)
		return 0;

	if (dev->state & DEV_DISCONNECTED)
		return 0;

	if (urb->status < 0) {
		print_err_status(dev, -1, urb->status);
		if (urb->status == -ENOENT)
			return 0;
	}

	for (i = 0; i < urb->number_of_packets; i++) {
		int status = urb->iso_frame_desc[i].status;

		if (status < 0) {
			print_err_status(dev, i, status);
			if (urb->iso_frame_desc[i].status != -EPROTO)
				continue;
		}

		dvb_dmx_swfilter(&dev->dvb->demux,
				 urb->transfer_buffer +
				urb->iso_frame_desc[i].offset,
				urb->iso_frame_desc[i].actual_length);
	}

	return 0;
}