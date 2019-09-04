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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int num_reg; scalar_t__ page_size; } ;
struct mic_smpt_info {int /*<<< orphan*/  smpt_lock; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  map_count; TYPE_2__* entry; TYPE_1__ info; } ;
struct mic_device {struct mic_smpt_info* smpt; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {scalar_t__ dma_addr; scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  mic_add_smpt_entry (int,scalar_t__*,scalar_t__,int,struct mic_device*) ; 
 scalar_t__ mic_smpt_to_pa (struct mic_device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static dma_addr_t mic_smpt_op(struct mic_device *mdev, u64 dma_addr,
			      int entries, s64 *ref, size_t size)
{
	int spt;
	int ae = 0;
	int i;
	unsigned long flags;
	dma_addr_t mic_addr = 0;
	dma_addr_t addr = dma_addr;
	struct mic_smpt_info *smpt_info = mdev->smpt;

	spin_lock_irqsave(&smpt_info->smpt_lock, flags);

	/* find existing entries */
	for (i = 0; i < smpt_info->info.num_reg; i++) {
		if (smpt_info->entry[i].dma_addr == addr) {
			ae++;
			addr += smpt_info->info.page_size;
		} else if (ae) /* cannot find contiguous entries */
			goto not_found;

		if (ae == entries)
			goto found;
	}

	/* find free entry */
	for (ae = 0, i = 0; i < smpt_info->info.num_reg; i++) {
		ae = (smpt_info->entry[i].ref_count == 0) ? ae + 1 : 0;
		if (ae == entries)
			goto found;
	}

not_found:
	spin_unlock_irqrestore(&smpt_info->smpt_lock, flags);
	return mic_addr;

found:
	spt = i - entries + 1;
	mic_addr = mic_smpt_to_pa(mdev, spt);
	mic_add_smpt_entry(spt, ref, dma_addr, entries, mdev);
	smpt_info->map_count++;
	smpt_info->ref_count += (s64)size;
	spin_unlock_irqrestore(&smpt_info->smpt_lock, flags);
	return mic_addr;
}