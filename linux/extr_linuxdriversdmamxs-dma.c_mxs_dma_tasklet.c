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
struct mxs_dma_chan {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mxs_dma_tasklet(unsigned long data)
{
	struct mxs_dma_chan *mxs_chan = (struct mxs_dma_chan *) data;

	dmaengine_desc_get_callback_invoke(&mxs_chan->desc, NULL);
}