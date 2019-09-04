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
struct TYPE_2__ {int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_maxburst; } ;
struct idma64_chan {TYPE_1__ config; } ;
struct dma_slave_config {int /*<<< orphan*/  direction; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  convert_burst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_slave_direction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct dma_slave_config*,int) ; 
 struct idma64_chan* to_idma64_chan (struct dma_chan*) ; 

__attribute__((used)) static int idma64_slave_config(struct dma_chan *chan,
		struct dma_slave_config *config)
{
	struct idma64_chan *idma64c = to_idma64_chan(chan);

	/* Check if chan will be configured for slave transfers */
	if (!is_slave_direction(config->direction))
		return -EINVAL;

	memcpy(&idma64c->config, config, sizeof(idma64c->config));

	convert_burst(&idma64c->config.src_maxburst);
	convert_burst(&idma64c->config.dst_maxburst);

	return 0;
}