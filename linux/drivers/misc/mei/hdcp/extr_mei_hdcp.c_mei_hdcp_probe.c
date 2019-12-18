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
struct mei_cl_device_id {int dummy; } ;
struct mei_cl_device {int /*<<< orphan*/  dev; } ;
struct i915_hdcp_comp_master {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct component_match*) ; 
 int component_master_add_with_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  component_match_add_typed (int /*<<< orphan*/ *,struct component_match**,int /*<<< orphan*/ ,struct i915_hdcp_comp_master*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (struct i915_hdcp_comp_master*) ; 
 struct i915_hdcp_comp_master* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_cldev_disable (struct mei_cl_device*) ; 
 int mei_cldev_enable (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_cldev_set_drvdata (struct mei_cl_device*,struct i915_hdcp_comp_master*) ; 
 int /*<<< orphan*/  mei_component_master_ops ; 
 int /*<<< orphan*/  mei_hdcp_component_match ; 

__attribute__((used)) static int mei_hdcp_probe(struct mei_cl_device *cldev,
			  const struct mei_cl_device_id *id)
{
	struct i915_hdcp_comp_master *comp_master;
	struct component_match *master_match;
	int ret;

	ret = mei_cldev_enable(cldev);
	if (ret < 0) {
		dev_err(&cldev->dev, "mei_cldev_enable Failed. %d\n", ret);
		goto enable_err_exit;
	}

	comp_master = kzalloc(sizeof(*comp_master), GFP_KERNEL);
	if (!comp_master) {
		ret = -ENOMEM;
		goto err_exit;
	}

	master_match = NULL;
	component_match_add_typed(&cldev->dev, &master_match,
				  mei_hdcp_component_match, comp_master);
	if (IS_ERR_OR_NULL(master_match)) {
		ret = -ENOMEM;
		goto err_exit;
	}

	mei_cldev_set_drvdata(cldev, comp_master);
	ret = component_master_add_with_match(&cldev->dev,
					      &mei_component_master_ops,
					      master_match);
	if (ret < 0) {
		dev_err(&cldev->dev, "Master comp add failed %d\n", ret);
		goto err_exit;
	}

	return 0;

err_exit:
	mei_cldev_set_drvdata(cldev, NULL);
	kfree(comp_master);
	mei_cldev_disable(cldev);
enable_err_exit:
	return ret;
}