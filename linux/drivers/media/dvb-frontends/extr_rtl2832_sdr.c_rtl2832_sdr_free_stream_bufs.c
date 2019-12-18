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
struct rtl2832_sdr_dev {size_t buf_num; int /*<<< orphan*/  flags; int /*<<< orphan*/ * dma_addr; int /*<<< orphan*/ * buf_list; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  udev; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  URB_BUF ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl2832_sdr_free_stream_bufs(struct rtl2832_sdr_dev *dev)
{
	struct platform_device *pdev = dev->pdev;

	if (test_bit(URB_BUF, &dev->flags)) {
		while (dev->buf_num) {
			dev->buf_num--;
			dev_dbg(&pdev->dev, "free buf=%d\n", dev->buf_num);
			usb_free_coherent(dev->udev, dev->buf_size,
					  dev->buf_list[dev->buf_num],
					  dev->dma_addr[dev->buf_num]);
		}
	}
	clear_bit(URB_BUF, &dev->flags);

	return 0;
}