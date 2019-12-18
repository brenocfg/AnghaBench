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
struct sdma_desc {int dummy; } ;
struct hfi1_devdata {TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
#define  SDMA_MAP_PAGE 129 
#define  SDMA_MAP_SINGLE 128 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_mapping_addr (struct sdma_desc*) ; 
 int /*<<< orphan*/  sdma_mapping_len (struct sdma_desc*) ; 
 int sdma_mapping_type (struct sdma_desc*) ; 

__attribute__((used)) static inline void sdma_unmap_desc(
	struct hfi1_devdata *dd,
	struct sdma_desc *descp)
{
	switch (sdma_mapping_type(descp)) {
	case SDMA_MAP_SINGLE:
		dma_unmap_single(
			&dd->pcidev->dev,
			sdma_mapping_addr(descp),
			sdma_mapping_len(descp),
			DMA_TO_DEVICE);
		break;
	case SDMA_MAP_PAGE:
		dma_unmap_page(
			&dd->pcidev->dev,
			sdma_mapping_addr(descp),
			sdma_mapping_len(descp),
			DMA_TO_DEVICE);
		break;
	}
}