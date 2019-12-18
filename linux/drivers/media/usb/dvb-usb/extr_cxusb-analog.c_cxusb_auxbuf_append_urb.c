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
struct urb {int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ transfer_buffer; } ;
struct dvb_usb_device {int dummy; } ;
struct cxusb_medion_auxbuf {scalar_t__ paylen; scalar_t__ buf; } ;
struct TYPE_2__ {unsigned int actual_length; scalar_t__ offset; } ;

/* Variables and functions */
 int cxusb_auxbuf_make_space (struct dvb_usb_device*,struct cxusb_medion_auxbuf*,unsigned long) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,unsigned int) ; 

__attribute__((used)) static bool cxusb_auxbuf_append_urb(struct dvb_usb_device *dvbdev,
				    struct cxusb_medion_auxbuf *auxbuf,
				    struct urb *urb)
{
	unsigned long len;
	int i;
	bool ret;

	for (i = 0, len = 0; i < urb->number_of_packets; i++)
		len += urb->iso_frame_desc[i].actual_length;

	ret = cxusb_auxbuf_make_space(dvbdev, auxbuf, len);

	for (i = 0; i < urb->number_of_packets; i++) {
		unsigned int to_copy;

		to_copy = urb->iso_frame_desc[i].actual_length;

		memcpy(auxbuf->buf + auxbuf->paylen, urb->transfer_buffer +
		       urb->iso_frame_desc[i].offset, to_copy);

		auxbuf->paylen += to_copy;
	}

	return ret;
}