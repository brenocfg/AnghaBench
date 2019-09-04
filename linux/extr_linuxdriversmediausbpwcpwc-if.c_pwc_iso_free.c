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
struct pwc_device {TYPE_1__** urbs; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_dma; scalar_t__ transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; } ;

/* Variables and functions */
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  PWC_DEBUG_MEMORY (char*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 

__attribute__((used)) static void pwc_iso_free(struct pwc_device *pdev)
{
	int i;

	/* Freeing ISOC buffers one by one */
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		if (pdev->urbs[i]) {
			PWC_DEBUG_MEMORY("Freeing URB\n");
			if (pdev->urbs[i]->transfer_buffer) {
				usb_free_coherent(pdev->udev,
					pdev->urbs[i]->transfer_buffer_length,
					pdev->urbs[i]->transfer_buffer,
					pdev->urbs[i]->transfer_dma);
			}
			usb_free_urb(pdev->urbs[i]);
			pdev->urbs[i] = NULL;
		}
	}
}