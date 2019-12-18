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
struct thermal_cooling_device_ops {int dummy; } ;
struct thermal_cooling_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct thermal_cooling_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct thermal_cooling_device*) ; 
 struct thermal_cooling_device* __thermal_cooling_device_register (struct device_node*,char*,void*,struct thermal_cooling_device_ops const*) ; 
 int /*<<< orphan*/  devres_add (struct device*,struct thermal_cooling_device**) ; 
 struct thermal_cooling_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct thermal_cooling_device**) ; 
 int /*<<< orphan*/  thermal_cooling_device_release ; 

struct thermal_cooling_device *
devm_thermal_of_cooling_device_register(struct device *dev,
				struct device_node *np,
				char *type, void *devdata,
				const struct thermal_cooling_device_ops *ops)
{
	struct thermal_cooling_device **ptr, *tcd;

	ptr = devres_alloc(thermal_cooling_device_release, sizeof(*ptr),
			   GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	tcd = __thermal_cooling_device_register(np, type, devdata, ops);
	if (IS_ERR(tcd)) {
		devres_free(ptr);
		return tcd;
	}

	*ptr = tcd;
	devres_add(dev, ptr);

	return tcd;
}