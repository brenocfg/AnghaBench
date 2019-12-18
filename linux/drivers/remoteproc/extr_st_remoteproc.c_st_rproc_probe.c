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
struct st_rproc_config {int dummy; } ;
struct TYPE_2__ {int tx_block; int knows_txdone; int /*<<< orphan*/  rx_callback; int /*<<< orphan*/ * tx_done; struct device* dev; } ;
struct st_rproc {int /*<<< orphan*/  clk; struct mbox_chan** mbox_chan; TYPE_1__ mbox_client_vq1; TYPE_1__ mbox_client_vq0; int /*<<< orphan*/  clk_rate; struct st_rproc_config* config; } ;
struct device {struct device_node* of_node; } ;
struct rproc {int has_iommu; struct device dev; int /*<<< orphan*/  state; int /*<<< orphan*/  power; struct st_rproc* priv; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct mbox_chan {int dummy; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct mbox_chan*) ; 
 size_t MBOX_MAX ; 
 size_t MBOX_RX ; 
 size_t MBOX_TX ; 
 int PTR_ERR (struct mbox_chan*) ; 
 int /*<<< orphan*/  RPROC_RUNNING ; 
 size_t ST_RPROC_MAX_VRING ; 
 size_t ST_RPROC_VQ0 ; 
 size_t ST_RPROC_VQ1 ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mbox_free_channel (struct mbox_chan*) ; 
 struct mbox_chan* mbox_request_channel_byname (TYPE_1__*,char*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rproc*) ; 
 int rproc_add (struct rproc*) ; 
 struct rproc* rproc_alloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 
 int /*<<< orphan*/  st_rproc_match ; 
 int /*<<< orphan*/  st_rproc_mbox_callback_vq0 ; 
 int /*<<< orphan*/  st_rproc_mbox_callback_vq1 ; 
 int /*<<< orphan*/  st_rproc_ops ; 
 int st_rproc_parse_dt (struct platform_device*) ; 
 int st_rproc_state (struct platform_device*) ; 

__attribute__((used)) static int st_rproc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct of_device_id *match;
	struct st_rproc *ddata;
	struct device_node *np = dev->of_node;
	struct rproc *rproc;
	struct mbox_chan *chan;
	int enabled;
	int ret, i;

	match = of_match_device(st_rproc_match, dev);
	if (!match || !match->data) {
		dev_err(dev, "No device match found\n");
		return -ENODEV;
	}

	rproc = rproc_alloc(dev, np->name, &st_rproc_ops, NULL, sizeof(*ddata));
	if (!rproc)
		return -ENOMEM;

	rproc->has_iommu = false;
	ddata = rproc->priv;
	ddata->config = (struct st_rproc_config *)match->data;

	platform_set_drvdata(pdev, rproc);

	ret = st_rproc_parse_dt(pdev);
	if (ret)
		goto free_rproc;

	enabled = st_rproc_state(pdev);
	if (enabled < 0) {
		ret = enabled;
		goto free_clk;
	}

	if (enabled) {
		atomic_inc(&rproc->power);
		rproc->state = RPROC_RUNNING;
	} else {
		clk_set_rate(ddata->clk, ddata->clk_rate);
	}

	if (of_get_property(np, "mbox-names", NULL)) {
		ddata->mbox_client_vq0.dev		= dev;
		ddata->mbox_client_vq0.tx_done		= NULL;
		ddata->mbox_client_vq0.tx_block	= false;
		ddata->mbox_client_vq0.knows_txdone	= false;
		ddata->mbox_client_vq0.rx_callback	= st_rproc_mbox_callback_vq0;

		ddata->mbox_client_vq1.dev		= dev;
		ddata->mbox_client_vq1.tx_done		= NULL;
		ddata->mbox_client_vq1.tx_block	= false;
		ddata->mbox_client_vq1.knows_txdone	= false;
		ddata->mbox_client_vq1.rx_callback	= st_rproc_mbox_callback_vq1;

		/*
		 * To control a co-processor without IPC mechanism.
		 * This driver can be used without mbox and rpmsg.
		 */
		chan = mbox_request_channel_byname(&ddata->mbox_client_vq0, "vq0_rx");
		if (IS_ERR(chan)) {
			dev_err(&rproc->dev, "failed to request mbox chan 0\n");
			ret = PTR_ERR(chan);
			goto free_clk;
		}
		ddata->mbox_chan[ST_RPROC_VQ0 * MBOX_MAX + MBOX_RX] = chan;

		chan = mbox_request_channel_byname(&ddata->mbox_client_vq0, "vq0_tx");
		if (IS_ERR(chan)) {
			dev_err(&rproc->dev, "failed to request mbox chan 0\n");
			ret = PTR_ERR(chan);
			goto free_mbox;
		}
		ddata->mbox_chan[ST_RPROC_VQ0 * MBOX_MAX + MBOX_TX] = chan;

		chan = mbox_request_channel_byname(&ddata->mbox_client_vq1, "vq1_rx");
		if (IS_ERR(chan)) {
			dev_err(&rproc->dev, "failed to request mbox chan 1\n");
			ret = PTR_ERR(chan);
			goto free_mbox;
		}
		ddata->mbox_chan[ST_RPROC_VQ1 * MBOX_MAX + MBOX_RX] = chan;

		chan = mbox_request_channel_byname(&ddata->mbox_client_vq1, "vq1_tx");
		if (IS_ERR(chan)) {
			dev_err(&rproc->dev, "failed to request mbox chan 1\n");
			ret = PTR_ERR(chan);
			goto free_mbox;
		}
		ddata->mbox_chan[ST_RPROC_VQ1 * MBOX_MAX + MBOX_TX] = chan;
	}

	ret = rproc_add(rproc);
	if (ret)
		goto free_mbox;

	return 0;

free_mbox:
	for (i = 0; i < ST_RPROC_MAX_VRING * MBOX_MAX; i++)
		mbox_free_channel(ddata->mbox_chan[i]);
free_clk:
	clk_unprepare(ddata->clk);
free_rproc:
	rproc_free(rproc);
	return ret;
}