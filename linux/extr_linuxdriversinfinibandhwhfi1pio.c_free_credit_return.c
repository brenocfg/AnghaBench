#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hfi1_devdata {TYPE_3__* cr_base; TYPE_1__* pcidev; } ;
struct credit_return {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma; scalar_t__ va; } ;
struct TYPE_5__ {int num_possible_nodes; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TXE_NUM_CONTEXTS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 TYPE_2__ node_affinity ; 

void free_credit_return(struct hfi1_devdata *dd)
{
	int i;

	if (!dd->cr_base)
		return;
	for (i = 0; i < node_affinity.num_possible_nodes; i++) {
		if (dd->cr_base[i].va) {
			dma_free_coherent(&dd->pcidev->dev,
					  TXE_NUM_CONTEXTS *
					  sizeof(struct credit_return),
					  dd->cr_base[i].va,
					  dd->cr_base[i].dma);
		}
	}
	kfree(dd->cr_base);
	dd->cr_base = NULL;
}