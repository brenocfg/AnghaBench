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
struct ati_remote {int /*<<< orphan*/  outbuf_dma; int /*<<< orphan*/  outbuf; int /*<<< orphan*/  udev; int /*<<< orphan*/  inbuf_dma; int /*<<< orphan*/  inbuf; int /*<<< orphan*/  out_urb; int /*<<< orphan*/  irq_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_BUFSIZE ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ati_remote_free_buffers(struct ati_remote *ati_remote)
{
	usb_free_urb(ati_remote->irq_urb);
	usb_free_urb(ati_remote->out_urb);

	usb_free_coherent(ati_remote->udev, DATA_BUFSIZE,
		ati_remote->inbuf, ati_remote->inbuf_dma);

	usb_free_coherent(ati_remote->udev, DATA_BUFSIZE,
		ati_remote->outbuf, ati_remote->outbuf_dma);
}