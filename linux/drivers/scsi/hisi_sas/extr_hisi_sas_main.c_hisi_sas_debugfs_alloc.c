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
struct hisi_sas_itct {int dummy; } ;
struct hisi_sas_iost_itct_cache {int dummy; } ;
struct hisi_sas_iost {int dummy; } ;
struct hisi_sas_hw {int complete_hdr_size; TYPE_2__** debugfs_reg_array; TYPE_1__* debugfs_reg_port; } ;
struct hisi_sas_cmd_hdr {int dummy; } ;
struct hisi_hba {int n_phy; int queue_count; void* debugfs_itct; void* debugfs_itct_cache; void* debugfs_iost_cache; void* debugfs_iost; void** debugfs_cmd_hdr; void** debugfs_complete_hdr; void** debugfs_regs; void** debugfs_port_reg; int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  debugfs_dump_dentry; struct device* dev; struct hisi_sas_hw* hw; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int count; } ;
struct TYPE_3__ {int count; } ;

/* Variables and functions */
 size_t DEBUGFS_AXI ; 
 size_t DEBUGFS_GLOBAL ; 
 size_t DEBUGFS_RAS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HISI_SAS_IOST_ITCT_CACHE_NUM ; 
 int HISI_SAS_MAX_COMMANDS ; 
 int HISI_SAS_MAX_ITCT_ENTRIES ; 
 int HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 void* devm_kmalloc (struct device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_release (struct hisi_hba*) ; 

__attribute__((used)) static int hisi_sas_debugfs_alloc(struct hisi_hba *hisi_hba)
{
	const struct hisi_sas_hw *hw = hisi_hba->hw;
	struct device *dev = hisi_hba->dev;
	int p, c, d;
	size_t sz;

	hisi_hba->debugfs_dump_dentry =
			debugfs_create_dir("dump", hisi_hba->debugfs_dir);

	sz = hw->debugfs_reg_array[DEBUGFS_GLOBAL]->count * 4;
	hisi_hba->debugfs_regs[DEBUGFS_GLOBAL] =
				devm_kmalloc(dev, sz, GFP_KERNEL);

	if (!hisi_hba->debugfs_regs[DEBUGFS_GLOBAL])
		goto fail;

	sz = hw->debugfs_reg_port->count * 4;
	for (p = 0; p < hisi_hba->n_phy; p++) {
		hisi_hba->debugfs_port_reg[p] =
			devm_kmalloc(dev, sz, GFP_KERNEL);

		if (!hisi_hba->debugfs_port_reg[p])
			goto fail;
	}

	sz = hw->debugfs_reg_array[DEBUGFS_AXI]->count * 4;
	hisi_hba->debugfs_regs[DEBUGFS_AXI] =
		devm_kmalloc(dev, sz, GFP_KERNEL);

	if (!hisi_hba->debugfs_regs[DEBUGFS_AXI])
		goto fail;

	sz = hw->debugfs_reg_array[DEBUGFS_RAS]->count * 4;
	hisi_hba->debugfs_regs[DEBUGFS_RAS] =
		devm_kmalloc(dev, sz, GFP_KERNEL);

	if (!hisi_hba->debugfs_regs[DEBUGFS_RAS])
		goto fail;

	sz = hw->complete_hdr_size * HISI_SAS_QUEUE_SLOTS;
	for (c = 0; c < hisi_hba->queue_count; c++) {
		hisi_hba->debugfs_complete_hdr[c] =
			devm_kmalloc(dev, sz, GFP_KERNEL);

		if (!hisi_hba->debugfs_complete_hdr[c])
			goto fail;
	}

	sz = sizeof(struct hisi_sas_cmd_hdr) * HISI_SAS_QUEUE_SLOTS;
	for (d = 0; d < hisi_hba->queue_count; d++) {
		hisi_hba->debugfs_cmd_hdr[d] =
			devm_kmalloc(dev, sz, GFP_KERNEL);

		if (!hisi_hba->debugfs_cmd_hdr[d])
			goto fail;
	}

	sz = HISI_SAS_MAX_COMMANDS * sizeof(struct hisi_sas_iost);

	hisi_hba->debugfs_iost = devm_kmalloc(dev, sz, GFP_KERNEL);
	if (!hisi_hba->debugfs_iost)
		goto fail;

	sz = HISI_SAS_IOST_ITCT_CACHE_NUM *
	     sizeof(struct hisi_sas_iost_itct_cache);

	hisi_hba->debugfs_iost_cache = devm_kmalloc(dev, sz, GFP_KERNEL);
	if (!hisi_hba->debugfs_iost_cache)
		goto fail;

	sz = HISI_SAS_IOST_ITCT_CACHE_NUM *
	     sizeof(struct hisi_sas_iost_itct_cache);

	hisi_hba->debugfs_itct_cache = devm_kmalloc(dev, sz, GFP_KERNEL);
	if (!hisi_hba->debugfs_itct_cache)
		goto fail;

	/* New memory allocation must be locate before itct */
	sz = HISI_SAS_MAX_ITCT_ENTRIES * sizeof(struct hisi_sas_itct);

	hisi_hba->debugfs_itct = devm_kmalloc(dev, sz, GFP_KERNEL);
	if (!hisi_hba->debugfs_itct)
		goto fail;

	return 0;
fail:
	hisi_sas_debugfs_release(hisi_hba);
	return -ENOMEM;
}