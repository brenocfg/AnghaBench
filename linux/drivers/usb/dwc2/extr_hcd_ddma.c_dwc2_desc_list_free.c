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
struct kmem_cache {int dummy; } ;
struct dwc2_qh {scalar_t__ ep_type; scalar_t__ dev_speed; int /*<<< orphan*/ * n_bytes; int /*<<< orphan*/ * desc_list; int /*<<< orphan*/  desc_list_sz; int /*<<< orphan*/  desc_list_dma; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; struct kmem_cache* desc_gen_cache; struct kmem_cache* desc_hsisoc_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc2_desc_list_free(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh)
{
	struct kmem_cache *desc_cache;

	if (qh->ep_type == USB_ENDPOINT_XFER_ISOC &&
	    qh->dev_speed == USB_SPEED_HIGH)
		desc_cache = hsotg->desc_hsisoc_cache;
	else
		desc_cache = hsotg->desc_gen_cache;

	if (qh->desc_list) {
		dma_unmap_single(hsotg->dev, qh->desc_list_dma,
				 qh->desc_list_sz, DMA_FROM_DEVICE);
		kmem_cache_free(desc_cache, qh->desc_list);
		qh->desc_list = NULL;
	}

	kfree(qh->n_bytes);
	qh->n_bytes = NULL;
}