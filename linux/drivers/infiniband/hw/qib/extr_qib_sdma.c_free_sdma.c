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
typedef  int /*<<< orphan*/  u64 ;
struct qib_pportdata {void* sdma_descq; int sdma_descq_cnt; scalar_t__ sdma_descq_phys; scalar_t__ sdma_head_phys; int /*<<< orphan*/ * sdma_head_dma; struct qib_devdata* dd; } ;
struct qib_devdata {TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,scalar_t__) ; 

__attribute__((used)) static void free_sdma(struct qib_pportdata *ppd)
{
	struct qib_devdata *dd = ppd->dd;

	if (ppd->sdma_head_dma) {
		dma_free_coherent(&dd->pcidev->dev, PAGE_SIZE,
				  (void *)ppd->sdma_head_dma,
				  ppd->sdma_head_phys);
		ppd->sdma_head_dma = NULL;
		ppd->sdma_head_phys = 0;
	}

	if (ppd->sdma_descq) {
		dma_free_coherent(&dd->pcidev->dev,
				  ppd->sdma_descq_cnt * sizeof(u64[2]),
				  ppd->sdma_descq, ppd->sdma_descq_phys);
		ppd->sdma_descq = NULL;
		ppd->sdma_descq_phys = 0;
	}
}