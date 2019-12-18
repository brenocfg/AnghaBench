#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdp_umem {unsigned int npgs; TYPE_1__* pages; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {TYPE_2__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  I40E_RX_DMA_ATTR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_xsk_umem_dma_unmap(struct i40e_vsi *vsi, struct xdp_umem *umem)
{
	struct i40e_pf *pf = vsi->back;
	struct device *dev;
	unsigned int i;

	dev = &pf->pdev->dev;

	for (i = 0; i < umem->npgs; i++) {
		dma_unmap_page_attrs(dev, umem->pages[i].dma, PAGE_SIZE,
				     DMA_BIDIRECTIONAL, I40E_RX_DMA_ATTR);

		umem->pages[i].dma = 0;
	}
}