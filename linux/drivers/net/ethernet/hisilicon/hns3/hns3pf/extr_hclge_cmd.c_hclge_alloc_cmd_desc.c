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
struct hclge_desc {int dummy; } ;
struct hclge_cmq_ring {int desc_num; int /*<<< orphan*/  desc; int /*<<< orphan*/  desc_dma_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cmq_ring_to_dev (struct hclge_cmq_ring*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_alloc_cmd_desc(struct hclge_cmq_ring *ring)
{
	int size  = ring->desc_num * sizeof(struct hclge_desc);

	ring->desc = dma_alloc_coherent(cmq_ring_to_dev(ring), size,
					&ring->desc_dma_addr, GFP_KERNEL);
	if (!ring->desc)
		return -ENOMEM;

	return 0;
}