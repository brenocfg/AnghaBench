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
typedef  int /*<<< orphan*/  u64 ;
struct mic_device {scalar_t__ family; TYPE_3__* pdev; TYPE_2__* smpt; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_reg; } ;
struct TYPE_5__ {TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MIC_FAMILY_X100 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mic_get_smpt_ref_count (struct mic_device*,scalar_t__,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t mic_max_system_memory (struct mic_device*) ; 
 scalar_t__ mic_smpt_offset (struct mic_device*,scalar_t__) ; 
 scalar_t__ mic_smpt_op (struct mic_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t) ; 

dma_addr_t mic_map(struct mic_device *mdev, dma_addr_t dma_addr, size_t size)
{
	dma_addr_t mic_addr = 0;
	int num_entries;
	s64 *ref;
	u64 smpt_start;

	if (!size || size > mic_max_system_memory(mdev))
		return mic_addr;

	ref = kmalloc_array(mdev->smpt->info.num_reg, sizeof(s64), GFP_ATOMIC);
	if (!ref)
		return mic_addr;

	num_entries = mic_get_smpt_ref_count(mdev, dma_addr, size,
					     ref, &smpt_start);

	/* Set the smpt table appropriately and get 16G aligned mic address */
	mic_addr = mic_smpt_op(mdev, smpt_start, num_entries, ref, size);

	kfree(ref);

	/*
	 * If mic_addr is zero then its an error case
	 * since mic_addr can never be zero.
	 * else generate mic_addr by adding the 16G offset in dma_addr
	 */
	if (!mic_addr && MIC_FAMILY_X100 == mdev->family) {
		dev_err(&mdev->pdev->dev,
			"mic_map failed dma_addr 0x%llx size 0x%lx\n",
			dma_addr, size);
		return mic_addr;
	} else {
		return mic_addr + mic_smpt_offset(mdev, dma_addr);
	}
}