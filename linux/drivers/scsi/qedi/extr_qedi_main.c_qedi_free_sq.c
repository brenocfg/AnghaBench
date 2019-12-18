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
struct qedi_endpoint {int /*<<< orphan*/  sq_dma; scalar_t__ sq; int /*<<< orphan*/  sq_mem_size; int /*<<< orphan*/  sq_pbl_dma; scalar_t__ sq_pbl; int /*<<< orphan*/  sq_pbl_size; } ;
struct qedi_ctx {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void qedi_free_sq(struct qedi_ctx *qedi, struct qedi_endpoint *ep)
{
	if (ep->sq_pbl)
		dma_free_coherent(&qedi->pdev->dev, ep->sq_pbl_size, ep->sq_pbl,
				  ep->sq_pbl_dma);
	if (ep->sq)
		dma_free_coherent(&qedi->pdev->dev, ep->sq_mem_size, ep->sq,
				  ep->sq_dma);
}