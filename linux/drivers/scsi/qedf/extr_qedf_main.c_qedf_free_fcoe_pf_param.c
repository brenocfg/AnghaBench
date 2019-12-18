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
struct qedf_glbl_q_params {int dummy; } ;
struct qedf_ctx {int num_queues; int /*<<< orphan*/  global_queues; int /*<<< orphan*/  hw_p_cpuq; scalar_t__ p_cpuq; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_free_global_queues (struct qedf_ctx*) ; 

__attribute__((used)) static void qedf_free_fcoe_pf_param(struct qedf_ctx *qedf)
{
	size_t size = 0;

	if (qedf->p_cpuq) {
		size = qedf->num_queues * sizeof(struct qedf_glbl_q_params);
		dma_free_coherent(&qedf->pdev->dev, size, qedf->p_cpuq,
		    qedf->hw_p_cpuq);
	}

	qedf_free_global_queues(qedf);

	kfree(qedf->global_queues);
}