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
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_ib_mr {int /*<<< orphan*/ * pages; int /*<<< orphan*/  page_map; int /*<<< orphan*/  page_map_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ib_device {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX4_MR_PAGES_ALIGN ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx4_alloc_priv_pages(struct ib_device *device,
		      struct mlx4_ib_mr *mr,
		      int max_pages)
{
	int ret;

	/* Ensure that size is aligned to DMA cacheline
	 * requirements.
	 * max_pages is limited to MLX4_MAX_FAST_REG_PAGES
	 * so page_map_size will never cross PAGE_SIZE.
	 */
	mr->page_map_size = roundup(max_pages * sizeof(u64),
				    MLX4_MR_PAGES_ALIGN);

	/* Prevent cross page boundary allocation. */
	mr->pages = (__be64 *)get_zeroed_page(GFP_KERNEL);
	if (!mr->pages)
		return -ENOMEM;

	mr->page_map = dma_map_single(device->dev.parent, mr->pages,
				      mr->page_map_size, DMA_TO_DEVICE);

	if (dma_mapping_error(device->dev.parent, mr->page_map)) {
		ret = -ENOMEM;
		goto err;
	}

	return 0;

err:
	free_page((unsigned long)mr->pages);
	return ret;
}