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
struct shdma_chan {scalar_t__ real_slave_id; } ;
struct dma_slave_config {scalar_t__ slave_id; scalar_t__ direction; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int shdma_setup_slave (struct shdma_chan*,int /*<<< orphan*/ ) ; 
 struct shdma_chan* to_shdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int shdma_config(struct dma_chan *chan,
			struct dma_slave_config *config)
{
	struct shdma_chan *schan = to_shdma_chan(chan);

	/*
	 * So far only .slave_id is used, but the slave drivers are
	 * encouraged to also set a transfer direction and an address.
	 */
	if (!config)
		return -EINVAL;

	/*
	 * overriding the slave_id through dma_slave_config is deprecated,
	 * but possibly some out-of-tree drivers still do it.
	 */
	if (WARN_ON_ONCE(config->slave_id &&
			 config->slave_id != schan->real_slave_id))
		schan->real_slave_id = config->slave_id;

	/*
	 * We could lock this, but you shouldn't be configuring the
	 * channel, while using it...
	 */
	return shdma_setup_slave(schan,
				 config->direction == DMA_DEV_TO_MEM ?
				 config->src_addr : config->dst_addr);
}