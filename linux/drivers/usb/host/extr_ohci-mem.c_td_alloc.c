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
struct td {int /*<<< orphan*/  td_dma; int /*<<< orphan*/  hwNextTD; } ;
struct ohci_hcd {int /*<<< orphan*/  td_cache; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_hc32 (struct ohci_hcd*,int /*<<< orphan*/ ) ; 
 struct td* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct td* gen_pool_dma_zalloc_align (scalar_t__,int,int /*<<< orphan*/ *,int) ; 
 struct usb_hcd* ohci_to_hcd (struct ohci_hcd*) ; 

__attribute__((used)) static struct td *
td_alloc (struct ohci_hcd *hc, gfp_t mem_flags)
{
	dma_addr_t	dma;
	struct td	*td;
	struct usb_hcd	*hcd = ohci_to_hcd(hc);

	if (hcd->localmem_pool)
		td = gen_pool_dma_zalloc_align(hcd->localmem_pool,
				sizeof(*td), &dma, 32);
	else
		td = dma_pool_zalloc(hc->td_cache, mem_flags, &dma);
	if (td) {
		/* in case hc fetches it, make it look dead */
		td->hwNextTD = cpu_to_hc32 (hc, dma);
		td->td_dma = dma;
		/* hashed in td_fill */
	}
	return td;
}