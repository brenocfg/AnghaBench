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
struct mic_smpt_info {TYPE_2__* entry; } ;
struct mic_device {TYPE_1__* pdev; struct mic_smpt_info* smpt; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {scalar_t__ dma_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  mic_is_system_addr (struct mic_device*,scalar_t__) ; 
 scalar_t__ mic_smpt_offset (struct mic_device*,scalar_t__) ; 
 int mic_sys_addr_to_smpt (struct mic_device*,scalar_t__) ; 

dma_addr_t mic_to_dma_addr(struct mic_device *mdev, dma_addr_t mic_addr)
{
	struct mic_smpt_info *smpt_info = mdev->smpt;
	int spt;
	dma_addr_t dma_addr;

	if (!mic_is_system_addr(mdev, mic_addr)) {
		dev_err(&mdev->pdev->dev,
			"mic_addr is invalid. mic_addr = 0x%llx\n", mic_addr);
		return -EINVAL;
	}
	spt = mic_sys_addr_to_smpt(mdev, mic_addr);
	dma_addr = smpt_info->entry[spt].dma_addr +
		mic_smpt_offset(mdev, mic_addr);
	return dma_addr;
}