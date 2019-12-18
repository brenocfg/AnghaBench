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
typedef  int u32 ;
struct be_fat_conf_params {TYPE_2__* module; int /*<<< orphan*/  num_modules; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; scalar_t__ va; } ;
struct be_cmd_resp_hdr {int dummy; } ;
struct be_cmd_resp_get_ext_fat_caps {int dummy; } ;
struct be_adapter {TYPE_3__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* trace_lvl; int /*<<< orphan*/  num_modes; } ;
struct TYPE_4__ {scalar_t__ mode; int /*<<< orphan*/  dbg_lvl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MODE_UART ; 
 int be_cmd_get_ext_fat_capabilites (struct be_adapter*,struct be_dma_mem*) ; 
 int be_cmd_set_ext_fat_capabilites (struct be_adapter*,struct be_dma_mem*,struct be_fat_conf_params*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 

int be_cmd_set_fw_log_level(struct be_adapter *adapter, u32 level)
{
	struct be_dma_mem extfat_cmd;
	struct be_fat_conf_params *cfgs;
	int status;
	int i, j;

	memset(&extfat_cmd, 0, sizeof(struct be_dma_mem));
	extfat_cmd.size = sizeof(struct be_cmd_resp_get_ext_fat_caps);
	extfat_cmd.va = dma_alloc_coherent(&adapter->pdev->dev,
					   extfat_cmd.size, &extfat_cmd.dma,
					   GFP_ATOMIC);
	if (!extfat_cmd.va)
		return -ENOMEM;

	status = be_cmd_get_ext_fat_capabilites(adapter, &extfat_cmd);
	if (status)
		goto err;

	cfgs = (struct be_fat_conf_params *)
			(extfat_cmd.va + sizeof(struct be_cmd_resp_hdr));
	for (i = 0; i < le32_to_cpu(cfgs->num_modules); i++) {
		u32 num_modes = le32_to_cpu(cfgs->module[i].num_modes);

		for (j = 0; j < num_modes; j++) {
			if (cfgs->module[i].trace_lvl[j].mode == MODE_UART)
				cfgs->module[i].trace_lvl[j].dbg_lvl =
							cpu_to_le32(level);
		}
	}

	status = be_cmd_set_ext_fat_capabilites(adapter, &extfat_cmd, cfgs);
err:
	dma_free_coherent(&adapter->pdev->dev, extfat_cmd.size, extfat_cmd.va,
			  extfat_cmd.dma);
	return status;
}