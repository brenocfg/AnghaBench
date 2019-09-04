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
struct mlx4_icm_buf {int size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  addr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_alloc_icm_coherent(struct device *dev, struct mlx4_icm_buf *buf,
				   int order, gfp_t gfp_mask)
{
	buf->addr = dma_alloc_coherent(dev, PAGE_SIZE << order,
				       &buf->dma_addr, gfp_mask);
	if (!buf->addr)
		return -ENOMEM;

	if (offset_in_page(buf->addr)) {
		dma_free_coherent(dev, PAGE_SIZE << order, buf->addr,
				  buf->dma_addr);
		return -ENOMEM;
	}

	buf->size = PAGE_SIZE << order;
	return 0;
}