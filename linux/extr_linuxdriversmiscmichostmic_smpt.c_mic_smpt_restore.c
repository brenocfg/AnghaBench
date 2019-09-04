#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mic_device {TYPE_4__* smpt_ops; TYPE_3__* smpt; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* set ) (struct mic_device*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int num_reg; } ;
struct TYPE_7__ {TYPE_2__* entry; TYPE_1__ info; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mic_device*,int /*<<< orphan*/ ,int) ; 

void mic_smpt_restore(struct mic_device *mdev)
{
	int i;
	dma_addr_t dma_addr;

	for (i = 0; i < mdev->smpt->info.num_reg; i++) {
		dma_addr = mdev->smpt->entry[i].dma_addr;
		mdev->smpt_ops->set(mdev, dma_addr, i);
	}
}