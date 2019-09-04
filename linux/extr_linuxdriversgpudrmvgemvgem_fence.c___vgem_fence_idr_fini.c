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

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (void*) ; 
 int /*<<< orphan*/  dma_fence_signal (void*) ; 

__attribute__((used)) static int __vgem_fence_idr_fini(int id, void *p, void *data)
{
	dma_fence_signal(p);
	dma_fence_put(p);
	return 0;
}