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
struct usb_hcd {int dummy; } ;
struct fhci_hcd {int /*<<< orphan*/ * pins; int /*<<< orphan*/ * gpios; int /*<<< orphan*/  pram; TYPE_1__* timer; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int NUM_GPIOS ; 
 int NUM_PINS ; 
 int /*<<< orphan*/  cpm_muram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpm_muram_offset (int /*<<< orphan*/ ) ; 
 struct usb_hcd* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fhci_dfs_destroy (struct fhci_hcd*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct usb_hcd*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtm_put_timer16 (TYPE_1__*) ; 
 struct fhci_hcd* hcd_to_fhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  qe_pin_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int fhci_remove(struct device *dev)
{
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct fhci_hcd *fhci = hcd_to_fhci(hcd);
	int i;
	int j;

	usb_remove_hcd(hcd);
	free_irq(fhci->timer->irq, hcd);
	gtm_put_timer16(fhci->timer);
	cpm_muram_free(cpm_muram_offset(fhci->pram));
	for (i = 0; i < NUM_GPIOS; i++) {
		if (!gpio_is_valid(fhci->gpios[i]))
			continue;
		gpio_free(fhci->gpios[i]);
	}
	for (j = 0; j < NUM_PINS; j++)
		qe_pin_free(fhci->pins[j]);
	fhci_dfs_destroy(fhci);
	usb_put_hcd(hcd);
	return 0;
}