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
struct device {int /*<<< orphan*/  of_node; } ;
struct rpmsg_device {int /*<<< orphan*/  ept; struct device dev; } ;
struct apr {int /*<<< orphan*/  svcs_idr; int /*<<< orphan*/  svcs_lock; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_list; int /*<<< orphan*/  rx_work; struct device* dev; int /*<<< orphan*/  rxwq; int /*<<< orphan*/  ch; int /*<<< orphan*/  dest_domain_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_rxwq ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct apr*) ; 
 struct apr* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_register_apr_devices (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apr_probe(struct rpmsg_device *rpdev)
{
	struct device *dev = &rpdev->dev;
	struct apr *apr;
	int ret;

	apr = devm_kzalloc(dev, sizeof(*apr), GFP_KERNEL);
	if (!apr)
		return -ENOMEM;

	ret = of_property_read_u32(dev->of_node, "qcom,apr-domain", &apr->dest_domain_id);
	if (ret) {
		dev_err(dev, "APR Domain ID not specified in DT\n");
		return ret;
	}

	dev_set_drvdata(dev, apr);
	apr->ch = rpdev->ept;
	apr->dev = dev;
	apr->rxwq = create_singlethread_workqueue("qcom_apr_rx");
	if (!apr->rxwq) {
		dev_err(apr->dev, "Failed to start Rx WQ\n");
		return -ENOMEM;
	}
	INIT_WORK(&apr->rx_work, apr_rxwq);
	INIT_LIST_HEAD(&apr->rx_list);
	spin_lock_init(&apr->rx_lock);
	spin_lock_init(&apr->svcs_lock);
	idr_init(&apr->svcs_idr);
	of_register_apr_devices(dev);

	return 0;
}