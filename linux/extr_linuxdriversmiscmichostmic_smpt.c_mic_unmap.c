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
struct TYPE_4__ {int /*<<< orphan*/  num_reg; } ;
struct mic_smpt_info {int /*<<< orphan*/  smpt_lock; TYPE_2__* entry; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  unmap_count; TYPE_1__ info; } ;
struct mic_device {TYPE_3__* pdev; struct mic_smpt_info* smpt; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mic_get_smpt_ref_count (struct mic_device*,int /*<<< orphan*/ ,size_t,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mic_is_system_addr (struct mic_device*,int /*<<< orphan*/ ) ; 
 int mic_sys_addr_to_smpt (struct mic_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mic_unmap(struct mic_device *mdev, dma_addr_t mic_addr, size_t size)
{
	struct mic_smpt_info *smpt_info = mdev->smpt;
	s64 *ref;
	int num_smpt;
	int spt;
	int i;
	unsigned long flags;

	if (!size)
		return;

	if (!mic_is_system_addr(mdev, mic_addr)) {
		dev_err(&mdev->pdev->dev,
			"invalid address: 0x%llx\n", mic_addr);
		return;
	}

	spt = mic_sys_addr_to_smpt(mdev, mic_addr);
	ref = kmalloc_array(mdev->smpt->info.num_reg, sizeof(s64), GFP_ATOMIC);
	if (!ref)
		return;

	/* Get number of smpt entries to be mapped, ref count array */
	num_smpt = mic_get_smpt_ref_count(mdev, mic_addr, size, ref, NULL);

	spin_lock_irqsave(&smpt_info->smpt_lock, flags);
	smpt_info->unmap_count++;
	smpt_info->ref_count -= (s64)size;

	for (i = spt; i < spt + num_smpt; i++) {
		smpt_info->entry[i].ref_count -= ref[i - spt];
		if (smpt_info->entry[i].ref_count < 0)
			dev_warn(&mdev->pdev->dev,
				 "ref count for entry %d is negative\n", i);
	}
	spin_unlock_irqrestore(&smpt_info->smpt_lock, flags);
	kfree(ref);
}