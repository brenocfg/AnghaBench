#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_icm_chunk {scalar_t__ nsg; int npages; TYPE_3__* sg; } ;
struct mlx4_dev {TYPE_2__* persist; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (TYPE_3__*) ; 

__attribute__((used)) static void mlx4_free_icm_pages(struct mlx4_dev *dev, struct mlx4_icm_chunk *chunk)
{
	int i;

	if (chunk->nsg > 0)
		dma_unmap_sg(&dev->persist->pdev->dev, chunk->sg, chunk->npages,
			     DMA_BIDIRECTIONAL);

	for (i = 0; i < chunk->npages; ++i)
		__free_pages(sg_page(&chunk->sg[i]),
			     get_order(chunk->sg[i].length));
}