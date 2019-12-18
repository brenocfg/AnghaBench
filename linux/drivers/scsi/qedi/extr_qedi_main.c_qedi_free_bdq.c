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
struct qedi_ctx {TYPE_2__* bdq; TYPE_1__* pdev; int /*<<< orphan*/  bdq_pbl_dma; scalar_t__ bdq_pbl; int /*<<< orphan*/  bdq_pbl_mem_size; int /*<<< orphan*/  bdq_pbl_list_dma; scalar_t__ bdq_pbl_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf_dma; scalar_t__ buf_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_BDQ_BUF_SIZE ; 
 int QEDI_BDQ_NUM ; 
 int /*<<< orphan*/  QEDI_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedi_free_bdq(struct qedi_ctx *qedi)
{
	int i;

	if (qedi->bdq_pbl_list)
		dma_free_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				  qedi->bdq_pbl_list, qedi->bdq_pbl_list_dma);

	if (qedi->bdq_pbl)
		dma_free_coherent(&qedi->pdev->dev, qedi->bdq_pbl_mem_size,
				  qedi->bdq_pbl, qedi->bdq_pbl_dma);

	for (i = 0; i < QEDI_BDQ_NUM; i++) {
		if (qedi->bdq[i].buf_addr) {
			dma_free_coherent(&qedi->pdev->dev, QEDI_BDQ_BUF_SIZE,
					  qedi->bdq[i].buf_addr,
					  qedi->bdq[i].buf_dma);
		}
	}
}