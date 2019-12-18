#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct els_plogi {int /*<<< orphan*/  els_resp_pyld_dma; scalar_t__ els_resp_pyld; int /*<<< orphan*/  rx_size; int /*<<< orphan*/  els_plogi_pyld_dma; scalar_t__ els_plogi_pyld; int /*<<< orphan*/  tx_size; } ;
struct TYPE_7__ {TYPE_2__* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void qla2x00_els_dcmd2_free(scsi_qla_host_t *vha, struct els_plogi *els_plogi)
{
	if (els_plogi->els_plogi_pyld)
		dma_free_coherent(&vha->hw->pdev->dev,
				  els_plogi->tx_size,
				  els_plogi->els_plogi_pyld,
				  els_plogi->els_plogi_pyld_dma);

	if (els_plogi->els_resp_pyld)
		dma_free_coherent(&vha->hw->pdev->dev,
				  els_plogi->rx_size,
				  els_plogi->els_resp_pyld,
				  els_plogi->els_resp_pyld_dma);
}