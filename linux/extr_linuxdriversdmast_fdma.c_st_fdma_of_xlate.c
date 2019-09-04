#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* dev; } ;
struct st_fdma_dev {TYPE_3__* slim_rproc; int /*<<< orphan*/  dev; TYPE_4__ dma_device; } ;
struct TYPE_6__ {scalar_t__ of_node; int req_line; int req_ctrl; int type; } ;
struct st_fdma_chan {int dreq_line; TYPE_2__ cfg; } ;
struct of_phandle_args {int args_count; scalar_t__ np; int* args; } ;
struct of_dma {struct st_fdma_dev* of_dma_data; } ;
struct dma_chan {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  rproc; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 struct dma_chan* ERR_PTR (int) ; 
 int FDMA_REQ_CTRL_CFG_MASK ; 
 scalar_t__ IS_ERR_VALUE (int) ; 
 int ST_FDMA_TYPE_FREE_RUN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct dma_chan* dma_get_any_slave_channel (TYPE_4__*) ; 
 int rproc_boot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_shutdown (int /*<<< orphan*/ ) ; 
 int st_fdma_dreq_get (struct st_fdma_chan*) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *st_fdma_of_xlate(struct of_phandle_args *dma_spec,
					 struct of_dma *ofdma)
{
	struct st_fdma_dev *fdev = ofdma->of_dma_data;
	struct dma_chan *chan;
	struct st_fdma_chan *fchan;
	int ret;

	if (dma_spec->args_count < 1)
		return ERR_PTR(-EINVAL);

	if (fdev->dma_device.dev->of_node != dma_spec->np)
		return ERR_PTR(-EINVAL);

	ret = rproc_boot(fdev->slim_rproc->rproc);
	if (ret == -ENOENT)
		return ERR_PTR(-EPROBE_DEFER);
	else if (ret)
		return ERR_PTR(ret);

	chan = dma_get_any_slave_channel(&fdev->dma_device);
	if (!chan)
		goto err_chan;

	fchan = to_st_fdma_chan(chan);

	fchan->cfg.of_node = dma_spec->np;
	fchan->cfg.req_line = dma_spec->args[0];
	fchan->cfg.req_ctrl = 0;
	fchan->cfg.type = ST_FDMA_TYPE_FREE_RUN;

	if (dma_spec->args_count > 1)
		fchan->cfg.req_ctrl = dma_spec->args[1]
			& FDMA_REQ_CTRL_CFG_MASK;

	if (dma_spec->args_count > 2)
		fchan->cfg.type = dma_spec->args[2];

	if (fchan->cfg.type == ST_FDMA_TYPE_FREE_RUN) {
		fchan->dreq_line = 0;
	} else {
		fchan->dreq_line = st_fdma_dreq_get(fchan);
		if (IS_ERR_VALUE(fchan->dreq_line)) {
			chan = ERR_PTR(fchan->dreq_line);
			goto err_chan;
		}
	}

	dev_dbg(fdev->dev, "xlate req_line:%d type:%d req_ctrl:%#lx\n",
		fchan->cfg.req_line, fchan->cfg.type, fchan->cfg.req_ctrl);

	return chan;

err_chan:
	rproc_shutdown(fdev->slim_rproc->rproc);
	return chan;

}