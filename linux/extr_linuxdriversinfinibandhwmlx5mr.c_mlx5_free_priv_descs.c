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
struct TYPE_3__ {struct ib_device* device; } ;
struct mlx5_ib_mr {int max_descs; int desc_size; int /*<<< orphan*/ * descs; int /*<<< orphan*/  descs_alloc; int /*<<< orphan*/  desc_map; TYPE_1__ ibmr; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ib_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlx5_free_priv_descs(struct mlx5_ib_mr *mr)
{
	if (mr->descs) {
		struct ib_device *device = mr->ibmr.device;
		int size = mr->max_descs * mr->desc_size;

		dma_unmap_single(device->dev.parent, mr->desc_map,
				 size, DMA_TO_DEVICE);
		kfree(mr->descs_alloc);
		mr->descs = NULL;
	}
}