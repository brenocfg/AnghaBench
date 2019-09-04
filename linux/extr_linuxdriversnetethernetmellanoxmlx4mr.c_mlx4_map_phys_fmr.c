#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct mlx4_fmr {unsigned long long page_shift; TYPE_5__* mpt; int /*<<< orphan*/  dma_handle; void** mtts; TYPE_2__ mr; int /*<<< orphan*/  maps; } ;
struct TYPE_6__ {scalar_t__ num_mpts; } ;
struct mlx4_dev {TYPE_4__* persist; TYPE_1__ caps; } ;
struct TYPE_10__ {void* start; void* length; void* lkey; void* key; } ;
struct TYPE_9__ {TYPE_3__* pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  MLX4_MPT_STATUS_HW ; 
 int /*<<< orphan*/  MLX4_MPT_STATUS_SW ; 
 int MLX4_MTT_FLAG_PRESENT ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_index_to_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_to_hw_index (int /*<<< orphan*/ ) ; 
 int mlx4_check_fmr (struct mlx4_fmr*,int*,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

int mlx4_map_phys_fmr(struct mlx4_dev *dev, struct mlx4_fmr *fmr, u64 *page_list,
		      int npages, u64 iova, u32 *lkey, u32 *rkey)
{
	u32 key;
	int i, err;

	err = mlx4_check_fmr(fmr, page_list, npages, iova);
	if (err)
		return err;

	++fmr->maps;

	key = key_to_hw_index(fmr->mr.key);
	key += dev->caps.num_mpts;
	*lkey = *rkey = fmr->mr.key = hw_index_to_key(key);

	*(u8 *) fmr->mpt = MLX4_MPT_STATUS_SW;

	/* Make sure MPT status is visible before writing MTT entries */
	wmb();

	dma_sync_single_for_cpu(&dev->persist->pdev->dev, fmr->dma_handle,
				npages * sizeof(u64), DMA_TO_DEVICE);

	for (i = 0; i < npages; ++i)
		fmr->mtts[i] = cpu_to_be64(page_list[i] | MLX4_MTT_FLAG_PRESENT);

	dma_sync_single_for_device(&dev->persist->pdev->dev, fmr->dma_handle,
				   npages * sizeof(u64), DMA_TO_DEVICE);

	fmr->mpt->key    = cpu_to_be32(key);
	fmr->mpt->lkey   = cpu_to_be32(key);
	fmr->mpt->length = cpu_to_be64(npages * (1ull << fmr->page_shift));
	fmr->mpt->start  = cpu_to_be64(iova);

	/* Make MTT entries are visible before setting MPT status */
	wmb();

	*(u8 *) fmr->mpt = MLX4_MPT_STATUS_HW;

	/* Make sure MPT status is visible before consumer can use FMR */
	wmb();

	return 0;
}