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
struct drm_file {int /*<<< orphan*/  master; TYPE_1__* minor; } ;
struct drm_device {int /*<<< orphan*/  master_mutex; int /*<<< orphan*/  master; } ;
struct TYPE_2__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_master_get (int /*<<< orphan*/ ) ; 
 int drm_new_set_master (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_master_open(struct drm_file *file_priv)
{
	struct drm_device *dev = file_priv->minor->dev;
	int ret = 0;

	/* if there is no current master make this fd it, but do not create
	 * any master object for render clients */
	mutex_lock(&dev->master_mutex);
	if (!dev->master)
		ret = drm_new_set_master(dev, file_priv);
	else
		file_priv->master = drm_master_get(dev->master);
	mutex_unlock(&dev->master_mutex);

	return ret;
}