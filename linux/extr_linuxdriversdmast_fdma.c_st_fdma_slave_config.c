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
struct st_fdma_chan {int /*<<< orphan*/  scfg; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int st_fdma_slave_config(struct dma_chan *chan,
				struct dma_slave_config *slave_cfg)
{
	struct st_fdma_chan *fchan = to_st_fdma_chan(chan);

	memcpy(&fchan->scfg, slave_cfg, sizeof(fchan->scfg));
	return 0;
}