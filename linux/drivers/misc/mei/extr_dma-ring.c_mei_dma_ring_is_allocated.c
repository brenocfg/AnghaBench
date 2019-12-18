#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mei_device {TYPE_1__* dr_dscr; } ;
struct TYPE_2__ {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 size_t DMA_DSCR_HOST ; 

bool mei_dma_ring_is_allocated(struct mei_device *dev)
{
	return !!dev->dr_dscr[DMA_DSCR_HOST].vaddr;
}