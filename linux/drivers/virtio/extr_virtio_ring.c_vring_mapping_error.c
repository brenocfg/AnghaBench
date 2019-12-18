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
struct vring_virtqueue {int /*<<< orphan*/  use_dma_api; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_dma_dev (struct vring_virtqueue const*) ; 

__attribute__((used)) static int vring_mapping_error(const struct vring_virtqueue *vq,
			       dma_addr_t addr)
{
	if (!vq->use_dma_api)
		return 0;

	return dma_mapping_error(vring_dma_dev(vq), addr);
}