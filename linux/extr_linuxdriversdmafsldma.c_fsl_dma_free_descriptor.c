#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsldma_chan {int /*<<< orphan*/  desc_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; } ;
struct fsl_desc_sw {TYPE_1__ async_tx; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_dbg (struct fsldma_chan*,char*,struct fsl_desc_sw*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct fsl_desc_sw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_dma_free_descriptor(struct fsldma_chan *chan,
		struct fsl_desc_sw *desc)
{
	list_del(&desc->node);
	chan_dbg(chan, "LD %p free\n", desc);
	dma_pool_free(chan->desc_pool, desc, desc->async_tx.phys);
}