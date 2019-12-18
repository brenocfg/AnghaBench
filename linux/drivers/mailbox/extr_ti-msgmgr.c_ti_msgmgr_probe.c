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
struct ti_queue_inst {int dummy; } ;
typedef  struct ti_msgmgr_valid_queue_desc {int proxy_id; scalar_t__ queue_id; } const ti_msgmgr_valid_queue_desc ;
struct mbox_controller {int num_chans; int txdone_irq; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/  txpoll_period; scalar_t__ txdone_poll; struct mbox_chan* chans; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct ti_msgmgr_inst {int num_valid_queues; struct mbox_chan* chans; struct mbox_controller mbox; struct ti_queue_inst* qinsts; void* queue_state_debug_region; void* queue_proxy_region; void* queue_ctrl_region; struct ti_msgmgr_desc const* desc; struct device* dev; } ;
struct ti_msgmgr_desc {int num_valid_queues; int queue_count; int /*<<< orphan*/  tx_poll_timeout_ms; scalar_t__ tx_polled; struct ti_msgmgr_valid_queue_desc const* valid_queues; scalar_t__ is_sproxy; int /*<<< orphan*/  ctrl_region_name; int /*<<< orphan*/  status_region_name; int /*<<< orphan*/  data_region_name; } ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {struct ti_msgmgr_desc* data; } ;
struct mbox_chan {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_crit (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,void*,void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct ti_msgmgr_inst* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (struct device*,struct mbox_controller*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ti_msgmgr_inst*) ; 
 int /*<<< orphan*/  ti_msgmgr_chan_ops ; 
 int /*<<< orphan*/  ti_msgmgr_of_match ; 
 int /*<<< orphan*/  ti_msgmgr_of_xlate ; 
 int ti_msgmgr_queue_setup (int,struct device*,struct device_node*,struct ti_msgmgr_inst*,struct ti_msgmgr_desc const*,struct ti_msgmgr_valid_queue_desc const*,struct ti_queue_inst*,struct mbox_chan*) ; 

__attribute__((used)) static int ti_msgmgr_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct of_device_id *of_id;
	struct device_node *np;
	struct resource *res;
	const struct ti_msgmgr_desc *desc;
	struct ti_msgmgr_inst *inst;
	struct ti_queue_inst *qinst;
	struct mbox_controller *mbox;
	struct mbox_chan *chans;
	int queue_count;
	int i;
	int ret = -EINVAL;
	const struct ti_msgmgr_valid_queue_desc *queue_desc;

	if (!dev->of_node) {
		dev_err(dev, "no OF information\n");
		return -EINVAL;
	}
	np = dev->of_node;

	of_id = of_match_device(ti_msgmgr_of_match, dev);
	if (!of_id) {
		dev_err(dev, "OF data missing\n");
		return -EINVAL;
	}
	desc = of_id->data;

	inst = devm_kzalloc(dev, sizeof(*inst), GFP_KERNEL);
	if (!inst)
		return -ENOMEM;

	inst->dev = dev;
	inst->desc = desc;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   desc->data_region_name);
	inst->queue_proxy_region = devm_ioremap_resource(dev, res);
	if (IS_ERR(inst->queue_proxy_region))
		return PTR_ERR(inst->queue_proxy_region);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   desc->status_region_name);
	inst->queue_state_debug_region = devm_ioremap_resource(dev, res);
	if (IS_ERR(inst->queue_state_debug_region))
		return PTR_ERR(inst->queue_state_debug_region);

	if (desc->is_sproxy) {
		res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						   desc->ctrl_region_name);
		inst->queue_ctrl_region = devm_ioremap_resource(dev, res);
		if (IS_ERR(inst->queue_ctrl_region))
			return PTR_ERR(inst->queue_ctrl_region);
	}

	dev_dbg(dev, "proxy region=%p, queue_state=%p\n",
		inst->queue_proxy_region, inst->queue_state_debug_region);

	queue_count = desc->num_valid_queues;
	if (!queue_count || queue_count > desc->queue_count) {
		dev_crit(dev, "Invalid Number of queues %d. Max %d\n",
			 queue_count, desc->queue_count);
		return -ERANGE;
	}
	inst->num_valid_queues = queue_count;

	qinst = devm_kcalloc(dev, queue_count, sizeof(*qinst), GFP_KERNEL);
	if (!qinst)
		return -ENOMEM;
	inst->qinsts = qinst;

	chans = devm_kcalloc(dev, queue_count, sizeof(*chans), GFP_KERNEL);
	if (!chans)
		return -ENOMEM;
	inst->chans = chans;

	if (desc->is_sproxy) {
		struct ti_msgmgr_valid_queue_desc sproxy_desc;

		/* All proxies may be valid in Secure Proxy instance */
		for (i = 0; i < queue_count; i++, qinst++, chans++) {
			sproxy_desc.queue_id = 0;
			sproxy_desc.proxy_id = i;
			ret = ti_msgmgr_queue_setup(i, dev, np, inst,
						    desc, &sproxy_desc, qinst,
						    chans);
			if (ret)
				return ret;
		}
	} else {
		/* Only Some proxies are valid in Message Manager */
		for (i = 0, queue_desc = desc->valid_queues;
		     i < queue_count; i++, qinst++, chans++, queue_desc++) {
			ret = ti_msgmgr_queue_setup(i, dev, np, inst,
						    desc, queue_desc, qinst,
						    chans);
			if (ret)
				return ret;
		}
	}

	mbox = &inst->mbox;
	mbox->dev = dev;
	mbox->ops = &ti_msgmgr_chan_ops;
	mbox->chans = inst->chans;
	mbox->num_chans = inst->num_valid_queues;
	mbox->txdone_irq = false;
	mbox->txdone_poll = desc->tx_polled;
	if (desc->tx_polled)
		mbox->txpoll_period = desc->tx_poll_timeout_ms;
	mbox->of_xlate = ti_msgmgr_of_xlate;

	platform_set_drvdata(pdev, inst);
	ret = devm_mbox_controller_register(dev, mbox);
	if (ret)
		dev_err(dev, "Failed to register mbox_controller(%d)\n", ret);

	return ret;
}