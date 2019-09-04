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
struct pwc_device {scalar_t__* urbs; } ;

/* Variables and functions */
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  PWC_DEBUG_MEMORY (char*,scalar_t__) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static void pwc_iso_stop(struct pwc_device *pdev)
{
	int i;

	/* Unlinking ISOC buffers one by one */
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		if (pdev->urbs[i]) {
			PWC_DEBUG_MEMORY("Unlinking URB %p\n", pdev->urbs[i]);
			usb_kill_urb(pdev->urbs[i]);
		}
	}
}