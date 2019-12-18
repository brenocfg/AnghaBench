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
struct usb_hcd {scalar_t__ localmem_pool; } ;
struct ohci_hcd {int /*<<< orphan*/  ed_cache; } ;
struct ed {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct ed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_free (scalar_t__,unsigned long,int) ; 
 struct usb_hcd* ohci_to_hcd (struct ohci_hcd*) ; 

__attribute__((used)) static void
ed_free (struct ohci_hcd *hc, struct ed *ed)
{
	struct usb_hcd	*hcd = ohci_to_hcd(hc);

	if (hcd->localmem_pool)
		gen_pool_free(hcd->localmem_pool, (unsigned long)ed,
			      sizeof(*ed));
	else
		dma_pool_free(hc->ed_cache, ed, ed->dma);
}