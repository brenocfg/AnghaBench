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
struct reset_control {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct reset_control* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  devm_reset_control_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct reset_control**) ; 
 struct reset_control** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct reset_control**) ; 
 struct reset_control* of_reset_control_array_get (int /*<<< orphan*/ ,int,int,int) ; 

struct reset_control *
devm_reset_control_array_get(struct device *dev, bool shared, bool optional)
{
	struct reset_control **devres;
	struct reset_control *rstc;

	devres = devres_alloc(devm_reset_control_release, sizeof(*devres),
			      GFP_KERNEL);
	if (!devres)
		return ERR_PTR(-ENOMEM);

	rstc = of_reset_control_array_get(dev->of_node, shared, optional, true);
	if (IS_ERR(rstc)) {
		devres_free(devres);
		return rstc;
	}

	*devres = rstc;
	devres_add(dev, devres);

	return rstc;
}