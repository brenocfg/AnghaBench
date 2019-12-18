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
struct mipi_dsi_device {int /*<<< orphan*/  name; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MIPI_DSI_MODULE_PREFIX ; 
 int /*<<< orphan*/  add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_device_uevent_modalias (struct device*,struct kobj_uevent_env*) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (struct device*) ; 

__attribute__((used)) static int mipi_dsi_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	int err;

	err = of_device_uevent_modalias(dev, env);
	if (err != -ENODEV)
		return err;

	add_uevent_var(env, "MODALIAS=%s%s", MIPI_DSI_MODULE_PREFIX,
		       dsi->name);

	return 0;
}