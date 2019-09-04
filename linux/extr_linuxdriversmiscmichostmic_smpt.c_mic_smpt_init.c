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
struct TYPE_4__ {int num_reg; int page_size; } ;
struct mic_smpt_info {scalar_t__ unmap_count; scalar_t__ map_count; scalar_t__ ref_count; TYPE_3__* entry; TYPE_1__ info; int /*<<< orphan*/  smpt_lock; } ;
struct mic_device {TYPE_2__* smpt_ops; struct mic_smpt_info* smpt; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {int dma_addr; scalar_t__ ref_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set ) (struct mic_device*,int,int) ;int /*<<< orphan*/  (* init ) (struct mic_device*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mic_smpt_info*) ; 
 struct mic_smpt_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mic_device*) ; 
 int /*<<< orphan*/  stub2 (struct mic_device*,int,int) ; 

int mic_smpt_init(struct mic_device *mdev)
{
	int i, err = 0;
	dma_addr_t dma_addr;
	struct mic_smpt_info *smpt_info;

	mdev->smpt = kmalloc(sizeof(*mdev->smpt), GFP_KERNEL);
	if (!mdev->smpt)
		return -ENOMEM;

	smpt_info = mdev->smpt;
	mdev->smpt_ops->init(mdev);
	smpt_info->entry = kmalloc_array(smpt_info->info.num_reg,
					 sizeof(*smpt_info->entry), GFP_KERNEL);
	if (!smpt_info->entry) {
		err = -ENOMEM;
		goto free_smpt;
	}
	spin_lock_init(&smpt_info->smpt_lock);
	for (i = 0; i < smpt_info->info.num_reg; i++) {
		dma_addr = i * smpt_info->info.page_size;
		smpt_info->entry[i].dma_addr = dma_addr;
		smpt_info->entry[i].ref_count = 0;
		mdev->smpt_ops->set(mdev, dma_addr, i);
	}
	smpt_info->ref_count = 0;
	smpt_info->map_count = 0;
	smpt_info->unmap_count = 0;
	return 0;
free_smpt:
	kfree(smpt_info);
	return err;
}