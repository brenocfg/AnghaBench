#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scatterlist {int dummy; } ;
struct mlx5_ib_mr {int desc_size; int max_descs; scalar_t__ access_mode; int /*<<< orphan*/  desc_map; scalar_t__ ndescs; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ MLX5_MKC_ACCESS_MODE_KLMS ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_sg_to_pages (struct ib_mr*,struct scatterlist*,int,unsigned int*,int /*<<< orphan*/ ) ; 
 int mlx5_ib_sg_to_klms (struct mlx5_ib_mr*,struct scatterlist*,int,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_set_page ; 
 struct mlx5_ib_mr* to_mmr (struct ib_mr*) ; 

int mlx5_ib_map_mr_sg(struct ib_mr *ibmr, struct scatterlist *sg, int sg_nents,
		      unsigned int *sg_offset)
{
	struct mlx5_ib_mr *mr = to_mmr(ibmr);
	int n;

	mr->ndescs = 0;

	ib_dma_sync_single_for_cpu(ibmr->device, mr->desc_map,
				   mr->desc_size * mr->max_descs,
				   DMA_TO_DEVICE);

	if (mr->access_mode == MLX5_MKC_ACCESS_MODE_KLMS)
		n = mlx5_ib_sg_to_klms(mr, sg, sg_nents, sg_offset, NULL, 0,
				       NULL);
	else
		n = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset,
				mlx5_set_page);

	ib_dma_sync_single_for_device(ibmr->device, mr->desc_map,
				      mr->desc_size * mr->max_descs,
				      DMA_TO_DEVICE);

	return n;
}