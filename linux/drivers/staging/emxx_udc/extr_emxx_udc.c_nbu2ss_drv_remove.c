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
struct platform_device {int dummy; } ;
struct nbu2ss_udc {struct nbu2ss_ep* ep; } ;
struct nbu2ss_ep {int /*<<< orphan*/  phys_buf; scalar_t__ virt_buf; } ;

/* Variables and functions */
 int NUM_ENDPOINTS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct nbu2ss_udc*) ; 
 struct nbu2ss_udc udc_controller ; 
 int /*<<< orphan*/  vbus_irq ; 

__attribute__((used)) static int nbu2ss_drv_remove(struct platform_device *pdev)
{
	struct nbu2ss_udc	*udc;
	struct nbu2ss_ep	*ep;
	int	i;

	udc = &udc_controller;

	for (i = 0; i < NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];
		if (ep->virt_buf)
			dma_free_coherent(NULL, PAGE_SIZE, (void *)ep->virt_buf,
					  ep->phys_buf);
	}

	/* Interrupt Handler - Release */
	free_irq(vbus_irq, udc);

	return 0;
}