#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct sii8620 {TYPE_2__* dev; TYPE_1__ extcon_nb; int /*<<< orphan*/  extcon_wq; struct extcon_dev* extcon; } ;
struct extcon_dev {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EXTCON_DISP_MHL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct extcon_dev*) ; 
 int PTR_ERR (struct extcon_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 struct extcon_dev* extcon_find_edev_by_node (struct device_node*) ; 
 int extcon_register_notifier (struct extcon_dev*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 struct device_node* of_graph_get_remote_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  sii8620_extcon_notifier ; 
 int /*<<< orphan*/  sii8620_extcon_work ; 

__attribute__((used)) static int sii8620_extcon_init(struct sii8620 *ctx)
{
	struct extcon_dev *edev;
	struct device_node *musb, *muic;
	int ret;

	/* get micro-USB connector node */
	musb = of_graph_get_remote_node(ctx->dev->of_node, 1, -1);
	/* next get micro-USB Interface Controller node */
	muic = of_get_next_parent(musb);

	if (!muic) {
		dev_info(ctx->dev, "no extcon found, switching to 'always on' mode\n");
		return 0;
	}

	edev = extcon_find_edev_by_node(muic);
	of_node_put(muic);
	if (IS_ERR(edev)) {
		if (PTR_ERR(edev) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		dev_err(ctx->dev, "Invalid or missing extcon\n");
		return PTR_ERR(edev);
	}

	ctx->extcon = edev;
	ctx->extcon_nb.notifier_call = sii8620_extcon_notifier;
	INIT_WORK(&ctx->extcon_wq, sii8620_extcon_work);
	ret = extcon_register_notifier(edev, EXTCON_DISP_MHL, &ctx->extcon_nb);
	if (ret) {
		dev_err(ctx->dev, "failed to register notifier for MHL\n");
		return ret;
	}

	return 0;
}