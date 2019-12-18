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
struct urb {int /*<<< orphan*/  transfer_dma; scalar_t__ transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; TYPE_1__* dev; } ;
struct pwc_device {struct urb** urbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  PWC_DEBUG_MEMORY (char*) ; 
 int /*<<< orphan*/  pwc_free_urb_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void pwc_iso_free(struct pwc_device *pdev)
{
	int i;

	/* Freeing ISOC buffers one by one */
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		struct urb *urb = pdev->urbs[i];

		if (urb) {
			PWC_DEBUG_MEMORY("Freeing URB\n");
			if (urb->transfer_buffer)
				pwc_free_urb_buffer(&urb->dev->dev,
						    urb->transfer_buffer_length,
						    urb->transfer_buffer,
						    urb->transfer_dma);
			usb_free_urb(urb);
			pdev->urbs[i] = NULL;
		}
	}
}