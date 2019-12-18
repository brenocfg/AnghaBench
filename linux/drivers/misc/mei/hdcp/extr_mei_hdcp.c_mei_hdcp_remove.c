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
struct mei_cl_device {int /*<<< orphan*/  dev; } ;
struct i915_hdcp_comp_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_master_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i915_hdcp_comp_master*) ; 
 int mei_cldev_disable (struct mei_cl_device*) ; 
 struct i915_hdcp_comp_master* mei_cldev_get_drvdata (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_cldev_set_drvdata (struct mei_cl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_component_master_ops ; 

__attribute__((used)) static int mei_hdcp_remove(struct mei_cl_device *cldev)
{
	struct i915_hdcp_comp_master *comp_master =
						mei_cldev_get_drvdata(cldev);

	component_master_del(&cldev->dev, &mei_component_master_ops);
	kfree(comp_master);
	mei_cldev_set_drvdata(cldev, NULL);

	return mei_cldev_disable(cldev);
}