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
struct lpc32xx_usbd_dd_gad {int /*<<< orphan*/  this_dma; } ;
struct lpc32xx_udc {int /*<<< orphan*/  dd_cache; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 struct lpc32xx_usbd_dd_gad* dma_pool_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lpc32xx_usbd_dd_gad *udc_dd_alloc(struct lpc32xx_udc *udc)
{
	dma_addr_t			dma;
	struct lpc32xx_usbd_dd_gad	*dd;

	dd = dma_pool_alloc(udc->dd_cache, GFP_ATOMIC | GFP_DMA, &dma);
	if (dd)
		dd->this_dma = dma;

	return dd;
}