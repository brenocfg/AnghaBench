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
struct zx_dma_chan {int /*<<< orphan*/  slave_cfg; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct zx_dma_chan* to_zx_chan (struct dma_chan*) ; 

__attribute__((used)) static int zx_dma_config(struct dma_chan *chan,
			 struct dma_slave_config *cfg)
{
	struct zx_dma_chan *c = to_zx_chan(chan);

	if (!cfg)
		return -EINVAL;

	memcpy(&c->slave_cfg, cfg, sizeof(*cfg));

	return 0;
}