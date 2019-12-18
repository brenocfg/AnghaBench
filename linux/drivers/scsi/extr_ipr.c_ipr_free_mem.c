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
typedef  int /*<<< orphan*/  u32 ;
struct ipr_misc_cbs {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cfg_table; } ;
struct ipr_ioa_cfg {int hrrq_num; int cfg_table_size; int /*<<< orphan*/  trace; int /*<<< orphan*/ * hostrcb_dma; int /*<<< orphan*/ * hostrcb; TYPE_3__* pdev; int /*<<< orphan*/  cfg_table_dma; TYPE_2__ u; TYPE_1__* hrrq; int /*<<< orphan*/  vpd_cbs_dma; int /*<<< orphan*/  vpd_cbs; int /*<<< orphan*/  res_entries; } ;
struct ipr_hostrcb {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  host_rrq_dma; int /*<<< orphan*/  host_rrq; } ;

/* Variables and functions */
 int IPR_MAX_HCAMS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_free_cmd_blks (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_free_dump (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_free_mem(struct ipr_ioa_cfg *ioa_cfg)
{
	int i;

	kfree(ioa_cfg->res_entries);
	dma_free_coherent(&ioa_cfg->pdev->dev, sizeof(struct ipr_misc_cbs),
			  ioa_cfg->vpd_cbs, ioa_cfg->vpd_cbs_dma);
	ipr_free_cmd_blks(ioa_cfg);

	for (i = 0; i < ioa_cfg->hrrq_num; i++)
		dma_free_coherent(&ioa_cfg->pdev->dev,
				  sizeof(u32) * ioa_cfg->hrrq[i].size,
				  ioa_cfg->hrrq[i].host_rrq,
				  ioa_cfg->hrrq[i].host_rrq_dma);

	dma_free_coherent(&ioa_cfg->pdev->dev, ioa_cfg->cfg_table_size,
			  ioa_cfg->u.cfg_table, ioa_cfg->cfg_table_dma);

	for (i = 0; i < IPR_MAX_HCAMS; i++) {
		dma_free_coherent(&ioa_cfg->pdev->dev,
				  sizeof(struct ipr_hostrcb),
				  ioa_cfg->hostrcb[i],
				  ioa_cfg->hostrcb_dma[i]);
	}

	ipr_free_dump(ioa_cfg);
	kfree(ioa_cfg->trace);
}