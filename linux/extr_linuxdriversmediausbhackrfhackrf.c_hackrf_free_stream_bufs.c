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
struct hackrf_dev {int flags; int buf_num; int /*<<< orphan*/ * dma_addr; int /*<<< orphan*/ * buf_list; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  udev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int USB_STATE_URB_BUF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hackrf_free_stream_bufs(struct hackrf_dev *dev)
{
	if (dev->flags & USB_STATE_URB_BUF) {
		while (dev->buf_num) {
			dev->buf_num--;
			dev_dbg(dev->dev, "free buf=%d\n", dev->buf_num);
			usb_free_coherent(dev->udev, dev->buf_size,
					  dev->buf_list[dev->buf_num],
					  dev->dma_addr[dev->buf_num]);
		}
	}
	dev->flags &= ~USB_STATE_URB_BUF;

	return 0;
}