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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {scalar_t__ page_size; } ;
struct mic_smpt_info {TYPE_3__* entry; TYPE_1__ info; } ;
struct mic_device {TYPE_2__* smpt_ops; struct mic_smpt_info* smpt; } ;
typedef  scalar_t__ s64 ;
struct TYPE_6__ {scalar_t__ dma_addr; scalar_t__ ref_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set ) (struct mic_device*,scalar_t__,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mic_device*,scalar_t__,int) ; 

__attribute__((used)) static void mic_add_smpt_entry(int spt, s64 *ref, u64 addr,
			       int entries, struct mic_device *mdev)
{
	struct mic_smpt_info *smpt_info = mdev->smpt;
	int i;

	for (i = spt; i < spt + entries; i++,
		addr += smpt_info->info.page_size) {
		if (!smpt_info->entry[i].ref_count &&
		    (smpt_info->entry[i].dma_addr != addr)) {
			mdev->smpt_ops->set(mdev, addr, i);
			smpt_info->entry[i].dma_addr = addr;
		}
		smpt_info->entry[i].ref_count += ref[i - spt];
	}
}