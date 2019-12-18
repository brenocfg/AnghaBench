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
struct fhci_hcd {int /*<<< orphan*/ * usb_irq_stat; } ;

/* Variables and functions */

void fhci_dbg_isr(struct fhci_hcd *fhci, int usb_er)
{
	int i;

	if (usb_er == -1) {
		fhci->usb_irq_stat[12]++;
		return;
	}

	for (i = 0; i < 12; ++i) {
		if (usb_er & (1 << i))
			fhci->usb_irq_stat[i]++;
	}
}