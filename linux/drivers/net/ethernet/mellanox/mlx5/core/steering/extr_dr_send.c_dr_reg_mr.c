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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5dr_mr {size_t size; void* addr; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  mkey; } ;
struct mlx5_core_dev {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int dr_create_mkey (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_mr*) ; 
 struct mlx5dr_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 

__attribute__((used)) static struct mlx5dr_mr *dr_reg_mr(struct mlx5_core_dev *mdev,
				   u32 pdn, void *buf, size_t size)
{
	struct mlx5dr_mr *mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	struct device *dma_device;
	dma_addr_t dma_addr;
	int err;

	if (!mr)
		return NULL;

	dma_device = &mdev->pdev->dev;
	dma_addr = dma_map_single(dma_device, buf, size,
				  DMA_BIDIRECTIONAL);
	err = dma_mapping_error(dma_device, dma_addr);
	if (err) {
		mlx5_core_warn(mdev, "Can't dma buf\n");
		kfree(mr);
		return NULL;
	}

	err = dr_create_mkey(mdev, pdn, &mr->mkey);
	if (err) {
		mlx5_core_warn(mdev, "Can't create mkey\n");
		dma_unmap_single(dma_device, dma_addr, size,
				 DMA_BIDIRECTIONAL);
		kfree(mr);
		return NULL;
	}

	mr->dma_addr = dma_addr;
	mr->size = size;
	mr->addr = buf;

	return mr;
}