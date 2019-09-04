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
struct idma64_lli {int dummy; } ;
struct idma64_chan {int /*<<< orphan*/  pool; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct idma64_chan* to_idma64_chan (struct dma_chan*) ; 

__attribute__((used)) static int idma64_alloc_chan_resources(struct dma_chan *chan)
{
	struct idma64_chan *idma64c = to_idma64_chan(chan);

	/* Create a pool of consistent memory blocks for hardware descriptors */
	idma64c->pool = dma_pool_create(dev_name(chan2dev(chan)),
					chan->device->dev,
					sizeof(struct idma64_lli), 8, 0);
	if (!idma64c->pool) {
		dev_err(chan2dev(chan), "No memory for descriptors\n");
		return -ENOMEM;
	}

	return 0;
}