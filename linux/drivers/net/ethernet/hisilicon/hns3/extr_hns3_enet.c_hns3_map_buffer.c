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
struct hns3_enet_ring {int dummy; } ;
struct hns3_desc_cb {int /*<<< orphan*/  dma; int /*<<< orphan*/  length; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_to_dev (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  ring_to_dma_dir (struct hns3_enet_ring*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns3_map_buffer(struct hns3_enet_ring *ring, struct hns3_desc_cb *cb)
{
	cb->dma = dma_map_page(ring_to_dev(ring), cb->priv, 0,
			       cb->length, ring_to_dma_dir(ring));

	if (unlikely(dma_mapping_error(ring_to_dev(ring), cb->dma)))
		return -EIO;

	return 0;
}