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
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; } ;
struct of_dma {struct at_xdmac* of_dma_data; } ;
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;
struct at_xdmac_chan {int /*<<< orphan*/  perid; int /*<<< orphan*/  perif; int /*<<< orphan*/  memif; } ;
struct TYPE_2__ {struct device* dev; } ;
struct at_xdmac {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_XDMAC_DT_GET_MEM_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91_XDMAC_DT_GET_PERID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91_XDMAC_DT_GET_PER_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct dma_chan* dma_get_any_slave_channel (TYPE_1__*) ; 
 struct at_xdmac_chan* to_at_xdmac_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *at_xdmac_xlate(struct of_phandle_args *dma_spec,
				       struct of_dma *of_dma)
{
	struct at_xdmac		*atxdmac = of_dma->of_dma_data;
	struct at_xdmac_chan	*atchan;
	struct dma_chan		*chan;
	struct device		*dev = atxdmac->dma.dev;

	if (dma_spec->args_count != 1) {
		dev_err(dev, "dma phandler args: bad number of args\n");
		return NULL;
	}

	chan = dma_get_any_slave_channel(&atxdmac->dma);
	if (!chan) {
		dev_err(dev, "can't get a dma channel\n");
		return NULL;
	}

	atchan = to_at_xdmac_chan(chan);
	atchan->memif = AT91_XDMAC_DT_GET_MEM_IF(dma_spec->args[0]);
	atchan->perif = AT91_XDMAC_DT_GET_PER_IF(dma_spec->args[0]);
	atchan->perid = AT91_XDMAC_DT_GET_PERID(dma_spec->args[0]);
	dev_dbg(dev, "chan dt cfg: memif=%u perif=%u perid=%u\n",
		 atchan->memif, atchan->perif, atchan->perid);

	return chan;
}