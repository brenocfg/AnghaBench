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
struct ioatdma_device {int /*<<< orphan*/ * sed_hw_pool; } ;
struct ioat_sed_ent {unsigned int hw_pool; int /*<<< orphan*/  hw; int /*<<< orphan*/  dma; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioat_sed_cache ; 
 struct ioat_sed_ent* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ioat_sed_ent*) ; 

__attribute__((used)) static struct ioat_sed_ent *
ioat3_alloc_sed(struct ioatdma_device *ioat_dma, unsigned int hw_pool)
{
	struct ioat_sed_ent *sed;
	gfp_t flags = __GFP_ZERO | GFP_ATOMIC;

	sed = kmem_cache_alloc(ioat_sed_cache, flags);
	if (!sed)
		return NULL;

	sed->hw_pool = hw_pool;
	sed->hw = dma_pool_alloc(ioat_dma->sed_hw_pool[hw_pool],
				 flags, &sed->dma);
	if (!sed->hw) {
		kmem_cache_free(ioat_sed_cache, sed);
		return NULL;
	}

	return sed;
}