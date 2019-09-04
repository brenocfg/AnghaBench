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
struct zynqmp_dma_chan {int /*<<< orphan*/  done_list; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  active_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  zynqmp_dma_free_desc_list (struct zynqmp_dma_chan*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zynqmp_dma_free_descriptors(struct zynqmp_dma_chan *chan)
{
	zynqmp_dma_free_desc_list(chan, &chan->active_list);
	zynqmp_dma_free_desc_list(chan, &chan->pending_list);
	zynqmp_dma_free_desc_list(chan, &chan->done_list);
}