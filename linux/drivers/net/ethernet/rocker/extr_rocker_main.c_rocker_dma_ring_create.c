#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rocker_dma_ring_info {size_t size; unsigned int type; int /*<<< orphan*/  mapaddr; int /*<<< orphan*/ * desc; TYPE_1__* desc_info; scalar_t__ tail; scalar_t__ head; } ;
struct rocker {int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_DESC_ADDR (unsigned int) ; 
 int /*<<< orphan*/  DMA_DESC_CTRL (unsigned int) ; 
 int /*<<< orphan*/  DMA_DESC_SIZE (unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ROCKER_DMA_DESC_CTRL_RESET ; 
 TYPE_1__* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 size_t rocker_dma_ring_size_fix (size_t) ; 
 int /*<<< orphan*/  rocker_write32 (struct rocker const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rocker_write64 (struct rocker const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_dma_ring_create(const struct rocker *rocker,
				  unsigned int type,
				  size_t size,
				  struct rocker_dma_ring_info *info)
{
	int i;

	BUG_ON(size != rocker_dma_ring_size_fix(size));
	info->size = size;
	info->type = type;
	info->head = 0;
	info->tail = 0;
	info->desc_info = kcalloc(info->size, sizeof(*info->desc_info),
				  GFP_KERNEL);
	if (!info->desc_info)
		return -ENOMEM;

	info->desc = pci_alloc_consistent(rocker->pdev,
					  info->size * sizeof(*info->desc),
					  &info->mapaddr);
	if (!info->desc) {
		kfree(info->desc_info);
		return -ENOMEM;
	}

	for (i = 0; i < info->size; i++)
		info->desc_info[i].desc = &info->desc[i];

	rocker_write32(rocker, DMA_DESC_CTRL(info->type),
		       ROCKER_DMA_DESC_CTRL_RESET);
	rocker_write64(rocker, DMA_DESC_ADDR(info->type), info->mapaddr);
	rocker_write32(rocker, DMA_DESC_SIZE(info->type), info->size);

	return 0;
}