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
struct rocker_dma_ring_info {int size; int /*<<< orphan*/ * desc_info; } ;
struct rocker {struct rocker_dma_ring_info cmd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  rocker_dma_cmd_ring_wait_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rocker_dma_cmd_ring_waits_free(const struct rocker *rocker)
{
	const struct rocker_dma_ring_info *cmd_ring = &rocker->cmd_ring;
	int i;

	for (i = 0; i < cmd_ring->size; i++)
		rocker_dma_cmd_ring_wait_free(&cmd_ring->desc_info[i]);
}