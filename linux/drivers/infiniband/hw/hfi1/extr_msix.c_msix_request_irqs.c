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
struct sdma_engine {int /*<<< orphan*/  dd; } ;
struct hfi1_devdata {int num_sdma; int n_krcv_queues; struct sdma_engine* per_sdma; } ;
struct hfi1_ctxtdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_GENERAL ; 
 int /*<<< orphan*/  enable_sdma_srcs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  general_interrupt ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index_safe (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int msix_request_irq (struct hfi1_devdata*,struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msix_request_rcd_irq (struct hfi1_ctxtdata*) ; 
 int msix_request_sdma_irq (struct sdma_engine*) ; 

int msix_request_irqs(struct hfi1_devdata *dd)
{
	int i;
	int ret;

	ret = msix_request_irq(dd, dd, general_interrupt, NULL, 0, IRQ_GENERAL);
	if (ret < 0)
		return ret;

	for (i = 0; i < dd->num_sdma; i++) {
		struct sdma_engine *sde = &dd->per_sdma[i];

		ret = msix_request_sdma_irq(sde);
		if (ret)
			return ret;
		enable_sdma_srcs(sde->dd, i);
	}

	for (i = 0; i < dd->n_krcv_queues; i++) {
		struct hfi1_ctxtdata *rcd = hfi1_rcd_get_by_index_safe(dd, i);

		if (rcd)
			ret = msix_request_rcd_irq(rcd);
		hfi1_rcd_put(rcd);
		if (ret)
			return ret;
	}

	return 0;
}