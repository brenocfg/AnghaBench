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
struct sge_fl {size_t cidx; size_t size; int /*<<< orphan*/  avail; struct rx_sw_desc* sdesc; } ;
struct rx_sw_desc {int /*<<< orphan*/ * page; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buf_addr (struct rx_sw_desc*) ; 
 int /*<<< orphan*/  get_buf_size (struct adapter*,struct rx_sw_desc*) ; 
 scalar_t__ is_buf_mapped (struct rx_sw_desc*) ; 

__attribute__((used)) static void unmap_rx_buf(struct adapter *adapter, struct sge_fl *fl)
{
	struct rx_sw_desc *sdesc = &fl->sdesc[fl->cidx];

	if (is_buf_mapped(sdesc))
		dma_unmap_page(adapter->pdev_dev, get_buf_addr(sdesc),
			       get_buf_size(adapter, sdesc),
			       PCI_DMA_FROMDEVICE);
	sdesc->page = NULL;
	if (++fl->cidx == fl->size)
		fl->cidx = 0;
	fl->avail--;
}