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
typedef  union t3_wr {int dummy; } t3_wr ;
struct TYPE_6__ {int /*<<< orphan*/  workq; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct cxio_rdev {TYPE_3__ ctrl_qp; TYPE_2__ rnic_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  T3_CTRL_QP_ID ; 
 unsigned long T3_CTRL_QP_SIZE_LOG2 ; 
 int cxio_hal_clear_qp_ctx (struct cxio_rdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 

__attribute__((used)) static int cxio_hal_destroy_ctrl_qp(struct cxio_rdev *rdev_p)
{
	dma_free_coherent(&(rdev_p->rnic_info.pdev->dev),
			  (1UL << T3_CTRL_QP_SIZE_LOG2)
			  * sizeof(union t3_wr), rdev_p->ctrl_qp.workq,
			  dma_unmap_addr(&rdev_p->ctrl_qp, mapping));
	return cxio_hal_clear_qp_ctx(rdev_p, T3_CTRL_QP_ID);
}