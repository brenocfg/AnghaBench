#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct phy_ops {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/  class; } ;
struct phy {int id; TYPE_1__ dev; int /*<<< orphan*/ * pwr; struct phy_ops const* ops; int /*<<< orphan*/  mutex; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 struct phy* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct phy*) ; 
 struct phy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_class ; 
 int /*<<< orphan*/  phy_ida ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 scalar_t__ pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (TYPE_1__*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/ * regulator_get_optional (TYPE_1__*,char*) ; 

struct phy *phy_create(struct device *dev, struct device_node *node,
		       const struct phy_ops *ops)
{
	int ret;
	int id;
	struct phy *phy;

	if (WARN_ON(!dev))
		return ERR_PTR(-EINVAL);

	phy = kzalloc(sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return ERR_PTR(-ENOMEM);

	id = ida_simple_get(&phy_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		dev_err(dev, "unable to get id\n");
		ret = id;
		goto free_phy;
	}

	device_initialize(&phy->dev);
	mutex_init(&phy->mutex);

	phy->dev.class = phy_class;
	phy->dev.parent = dev;
	phy->dev.of_node = node ?: dev->of_node;
	phy->id = id;
	phy->ops = ops;

	ret = dev_set_name(&phy->dev, "phy-%s.%d", dev_name(dev), id);
	if (ret)
		goto put_dev;

	/* phy-supply */
	phy->pwr = regulator_get_optional(&phy->dev, "phy");
	if (IS_ERR(phy->pwr)) {
		ret = PTR_ERR(phy->pwr);
		if (ret == -EPROBE_DEFER)
			goto put_dev;

		phy->pwr = NULL;
	}

	ret = device_add(&phy->dev);
	if (ret)
		goto put_dev;

	if (pm_runtime_enabled(dev)) {
		pm_runtime_enable(&phy->dev);
		pm_runtime_no_callbacks(&phy->dev);
	}

	return phy;

put_dev:
	put_device(&phy->dev);  /* calls phy_release() which frees resources */
	return ERR_PTR(ret);

free_phy:
	kfree(phy);
	return ERR_PTR(ret);
}