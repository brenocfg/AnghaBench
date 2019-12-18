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
struct airspy {int buf_num; int /*<<< orphan*/  flags; int /*<<< orphan*/ * dma_addr; int /*<<< orphan*/ * buf_list; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  udev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_STATE_URB_BUF ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int airspy_free_stream_bufs(struct airspy *s)
{
	if (test_bit(USB_STATE_URB_BUF, &s->flags)) {
		while (s->buf_num) {
			s->buf_num--;
			dev_dbg(s->dev, "free buf=%d\n", s->buf_num);
			usb_free_coherent(s->udev, s->buf_size,
					  s->buf_list[s->buf_num],
					  s->dma_addr[s->buf_num]);
		}
	}
	clear_bit(USB_STATE_URB_BUF, &s->flags);

	return 0;
}