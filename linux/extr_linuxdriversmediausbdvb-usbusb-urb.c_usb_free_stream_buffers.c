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
struct usb_data_stream {int state; int buf_num; int /*<<< orphan*/ * dma_addr; int /*<<< orphan*/ * buf_list; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int USB_STATE_URB_BUF ; 
 int /*<<< orphan*/  deb_mem (char*,int) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_free_stream_buffers(struct usb_data_stream *stream)
{
	if (stream->state & USB_STATE_URB_BUF) {
		while (stream->buf_num) {
			stream->buf_num--;
			deb_mem("freeing buffer %d\n",stream->buf_num);
			usb_free_coherent(stream->udev, stream->buf_size,
					  stream->buf_list[stream->buf_num],
					  stream->dma_addr[stream->buf_num]);
		}
	}

	stream->state &= ~USB_STATE_URB_BUF;

	return 0;
}