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
struct skd_device {TYPE_1__* pdev; } ;
struct kmem_cache {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  kmem_cache_size (struct kmem_cache*) ; 

__attribute__((used)) static void skd_free_dma(struct skd_device *skdev, struct kmem_cache *s,
			 void *vaddr, dma_addr_t dma_handle,
			 enum dma_data_direction dir)
{
	if (!vaddr)
		return;

	dma_unmap_single(&skdev->pdev->dev, dma_handle,
			 kmem_cache_size(s), dir);
	kmem_cache_free(s, vaddr);
}