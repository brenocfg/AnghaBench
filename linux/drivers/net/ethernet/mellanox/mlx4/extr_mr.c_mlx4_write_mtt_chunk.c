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
typedef  int u64 ;
struct TYPE_4__ {int /*<<< orphan*/  mtt_table; } ;
struct mlx4_priv {TYPE_1__ mr_table; } ;
struct mlx4_mtt {scalar_t__ offset; } ;
struct mlx4_dev {TYPE_3__* persist; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int MLX4_MTT_FLAG_PRESENT ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/ * mlx4_table_find (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx4_write_mtt_chunk(struct mlx4_dev *dev, struct mlx4_mtt *mtt,
				int start_index, int npages, u64 *page_list)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	__be64 *mtts;
	dma_addr_t dma_handle;
	int i;

	mtts = mlx4_table_find(&priv->mr_table.mtt_table, mtt->offset +
			       start_index, &dma_handle);

	if (!mtts)
		return -ENOMEM;

	dma_sync_single_for_cpu(&dev->persist->pdev->dev, dma_handle,
				npages * sizeof(u64), DMA_TO_DEVICE);

	for (i = 0; i < npages; ++i)
		mtts[i] = cpu_to_be64(page_list[i] | MLX4_MTT_FLAG_PRESENT);

	dma_sync_single_for_device(&dev->persist->pdev->dev, dma_handle,
				   npages * sizeof(u64), DMA_TO_DEVICE);

	return 0;
}