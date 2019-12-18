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
struct ipr_ioa_cfg {int /*<<< orphan*/ * ipr_cmd_pool; int /*<<< orphan*/ ** ipr_cmnd_list_dma; int /*<<< orphan*/ ** ipr_cmnd_list; } ;

/* Variables and functions */
 int IPR_NUM_CMD_BLKS ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void ipr_free_cmd_blks(struct ipr_ioa_cfg *ioa_cfg)
{
	int i;

	if (ioa_cfg->ipr_cmnd_list) {
		for (i = 0; i < IPR_NUM_CMD_BLKS; i++) {
			if (ioa_cfg->ipr_cmnd_list[i])
				dma_pool_free(ioa_cfg->ipr_cmd_pool,
					      ioa_cfg->ipr_cmnd_list[i],
					      ioa_cfg->ipr_cmnd_list_dma[i]);

			ioa_cfg->ipr_cmnd_list[i] = NULL;
		}
	}

	if (ioa_cfg->ipr_cmd_pool)
		dma_pool_destroy(ioa_cfg->ipr_cmd_pool);

	kfree(ioa_cfg->ipr_cmnd_list);
	kfree(ioa_cfg->ipr_cmnd_list_dma);
	ioa_cfg->ipr_cmnd_list = NULL;
	ioa_cfg->ipr_cmnd_list_dma = NULL;
	ioa_cfg->ipr_cmd_pool = NULL;
}