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
struct dma_slave_config {int dummy; } ;
struct pxad_chan {struct dma_slave_config cfg; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pxad_chan* to_pxad_chan (struct dma_chan*) ; 

__attribute__((used)) static int pxad_config(struct dma_chan *dchan,
		       struct dma_slave_config *cfg)
{
	struct pxad_chan *chan = to_pxad_chan(dchan);

	if (!dchan)
		return -EINVAL;

	chan->cfg = *cfg;
	return 0;
}