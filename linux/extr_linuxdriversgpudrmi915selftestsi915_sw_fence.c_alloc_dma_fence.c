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
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_fence* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_fence_lock ; 
 int /*<<< orphan*/  mock_fence_ops ; 

__attribute__((used)) static struct dma_fence *alloc_dma_fence(void)
{
	struct dma_fence *dma;

	dma = kmalloc(sizeof(*dma), GFP_KERNEL);
	if (dma)
		dma_fence_init(dma, &mock_fence_ops, &mock_fence_lock, 0, 0);

	return dma;
}