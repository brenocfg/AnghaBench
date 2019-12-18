#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  els_logo_pyld_dma; scalar_t__ els_logo_pyld; } ;
struct TYPE_14__ {TYPE_4__ els_logo; } ;
struct srb_iocb {int /*<<< orphan*/  timer; TYPE_5__ u; } ;
struct TYPE_12__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_16__ {TYPE_2__* vha; int /*<<< orphan*/  fcport; TYPE_3__ u; } ;
typedef  TYPE_7__ srb_t ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {TYPE_1__* hw; } ;
struct TYPE_10__ {TYPE_6__* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_POOL_SIZE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_rel_sp (TYPE_7__*) ; 

__attribute__((used)) static void qla2x00_els_dcmd_sp_free(srb_t *sp)
{
	struct srb_iocb *elsio = &sp->u.iocb_cmd;

	kfree(sp->fcport);

	if (elsio->u.els_logo.els_logo_pyld)
		dma_free_coherent(&sp->vha->hw->pdev->dev, DMA_POOL_SIZE,
		    elsio->u.els_logo.els_logo_pyld,
		    elsio->u.els_logo.els_logo_pyld_dma);

	del_timer(&elsio->timer);
	qla2x00_rel_sp(sp);
}