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
struct TYPE_2__ {int /*<<< orphan*/  usb_dev; } ;
struct as102_dev_t {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  stream; TYPE_1__ bus_adap; int /*<<< orphan*/ * stream_urb; } ;

/* Variables and functions */
 int AS102_USB_BUF_SIZE ; 
 int MAX_STREAM_URB ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void as102_free_usb_stream_buffer(struct as102_dev_t *dev)
{
	int i;

	for (i = 0; i < MAX_STREAM_URB; i++)
		usb_free_urb(dev->stream_urb[i]);

	usb_free_coherent(dev->bus_adap.usb_dev,
			MAX_STREAM_URB * AS102_USB_BUF_SIZE,
			dev->stream,
			dev->dma_addr);
}