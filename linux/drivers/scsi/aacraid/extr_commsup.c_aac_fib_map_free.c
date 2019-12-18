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
struct aac_fib_xporthdr {int dummy; } ;
struct aac_dev {int max_fib_size; int /*<<< orphan*/  hw_fib_pa; int /*<<< orphan*/ * hw_fib_va; TYPE_1__* pdev; TYPE_2__* scsi_host_ptr; int /*<<< orphan*/  max_cmd_size; } ;
struct TYPE_4__ {int can_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AAC_NUM_MGT_FIB ; 
 size_t ALIGN32 ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void aac_fib_map_free(struct aac_dev *dev)
{
	size_t alloc_size;
	size_t fib_size;
	int num_fibs;

	if(!dev->hw_fib_va || !dev->max_cmd_size)
		return;

	num_fibs = dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB;
	fib_size = dev->max_fib_size + sizeof(struct aac_fib_xporthdr);
	alloc_size = fib_size * num_fibs + ALIGN32 - 1;

	dma_free_coherent(&dev->pdev->dev, alloc_size, dev->hw_fib_va,
			  dev->hw_fib_pa);

	dev->hw_fib_va = NULL;
	dev->hw_fib_pa = 0;
}