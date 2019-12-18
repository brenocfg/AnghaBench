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
typedef  int /*<<< orphan*/  u16 ;
struct sdma_txreq {scalar_t__ num_desc; scalar_t__ desc_limit; } ;
struct hfi1_devdata {TYPE_1__* pcidev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOSPC ; 
 int /*<<< orphan*/  SDMA_MAP_SINGLE ; 
 int /*<<< orphan*/  __sdma_txclean (struct hfi1_devdata*,struct sdma_txreq*) ; 
 int _sdma_txadd_daddr (struct hfi1_devdata*,int /*<<< orphan*/ ,struct sdma_txreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ext_coal_sdma_tx_descs (struct hfi1_devdata*,struct sdma_txreq*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int sdma_txadd_kvaddr(
	struct hfi1_devdata *dd,
	struct sdma_txreq *tx,
	void *kvaddr,
	u16 len)
{
	dma_addr_t addr;
	int rval;

	if ((unlikely(tx->num_desc == tx->desc_limit))) {
		rval = ext_coal_sdma_tx_descs(dd, tx, SDMA_MAP_SINGLE,
					      kvaddr, NULL, 0, len);
		if (rval <= 0)
			return rval;
	}

	addr = dma_map_single(
		       &dd->pcidev->dev,
		       kvaddr,
		       len,
		       DMA_TO_DEVICE);

	if (unlikely(dma_mapping_error(&dd->pcidev->dev, addr))) {
		__sdma_txclean(dd, tx);
		return -ENOSPC;
	}

	return _sdma_txadd_daddr(
			dd, SDMA_MAP_SINGLE, tx, addr, len);
}