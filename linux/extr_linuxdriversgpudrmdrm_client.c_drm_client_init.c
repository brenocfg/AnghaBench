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
struct drm_device {TYPE_1__* driver; } ;
struct drm_client_funcs {int /*<<< orphan*/  owner; } ;
struct drm_client_dev {char const* name; struct drm_client_funcs const* funcs; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  gem_prime_vmap; int /*<<< orphan*/  dumb_create; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int ENODEV ; 
 int ENOTSUPP ; 
 int drm_client_open (struct drm_client_dev*) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_get (struct drm_device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int drm_client_init(struct drm_device *dev, struct drm_client_dev *client,
		    const char *name, const struct drm_client_funcs *funcs)
{
	int ret;

	if (!drm_core_check_feature(dev, DRIVER_MODESET) ||
	    !dev->driver->dumb_create || !dev->driver->gem_prime_vmap)
		return -ENOTSUPP;

	if (funcs && !try_module_get(funcs->owner))
		return -ENODEV;

	client->dev = dev;
	client->name = name;
	client->funcs = funcs;

	ret = drm_client_open(client);
	if (ret)
		goto err_put_module;

	drm_dev_get(dev);

	return 0;

err_put_module:
	if (funcs)
		module_put(funcs->owner);

	return ret;
}