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
struct hns3_enet_ring {int desc_num; int /*<<< orphan*/ * desc; int /*<<< orphan*/  desc_dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_free_buffers (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  ring_to_dev (struct hns3_enet_ring*) ; 

__attribute__((used)) static void hns3_free_desc(struct hns3_enet_ring *ring)
{
	int size = ring->desc_num * sizeof(ring->desc[0]);

	hns3_free_buffers(ring);

	if (ring->desc) {
		dma_free_coherent(ring_to_dev(ring), size,
				  ring->desc, ring->desc_dma_addr);
		ring->desc = NULL;
	}
}