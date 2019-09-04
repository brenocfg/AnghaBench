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
struct TYPE_3__ {int num_reg; } ;
struct mic_smpt_info {struct mic_smpt_info* entry; scalar_t__ ref_count; int /*<<< orphan*/  dma_addr; TYPE_1__ info; int /*<<< orphan*/  unmap_count; int /*<<< orphan*/  map_count; } ;
struct mic_device {TYPE_2__* pdev; int /*<<< orphan*/  id; struct mic_smpt_info* smpt; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (struct mic_smpt_info*) ; 

void mic_smpt_uninit(struct mic_device *mdev)
{
	struct mic_smpt_info *smpt_info = mdev->smpt;
	int i;

	dev_dbg(&mdev->pdev->dev,
		"nodeid %d SMPT ref count %lld map %lld unmap %lld\n",
		mdev->id, smpt_info->ref_count,
		smpt_info->map_count, smpt_info->unmap_count);

	for (i = 0; i < smpt_info->info.num_reg; i++) {
		dev_dbg(&mdev->pdev->dev,
			"SMPT entry[%d] dma_addr = 0x%llx ref_count = %lld\n",
			i, smpt_info->entry[i].dma_addr,
			smpt_info->entry[i].ref_count);
		if (smpt_info->entry[i].ref_count)
			dev_warn(&mdev->pdev->dev,
				 "ref count for entry %d is not zero\n", i);
	}
	kfree(smpt_info->entry);
	kfree(smpt_info);
}