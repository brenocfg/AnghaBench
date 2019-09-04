#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct vmci_queue {TYPE_2__* kernel_if; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pas; int /*<<< orphan*/ * vas; } ;
struct TYPE_7__ {TYPE_1__ g; } ;
struct TYPE_6__ {TYPE_3__ u; } ;

/* Variables and functions */
 size_t DIV_ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct vmci_queue*) ; 
 TYPE_4__* vmci_pdev ; 

__attribute__((used)) static void qp_free_queue(void *q, u64 size)
{
	struct vmci_queue *queue = q;

	if (queue) {
		u64 i;

		/* Given size does not include header, so add in a page here. */
		for (i = 0; i < DIV_ROUND_UP(size, PAGE_SIZE) + 1; i++) {
			dma_free_coherent(&vmci_pdev->dev, PAGE_SIZE,
					  queue->kernel_if->u.g.vas[i],
					  queue->kernel_if->u.g.pas[i]);
		}

		vfree(queue);
	}
}