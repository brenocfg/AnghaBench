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
struct drm_device {int dummy; } ;
struct drm_client_dev {struct drm_device* dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int drm_client_modeset_commit_force (struct drm_client_dev*) ; 
 int /*<<< orphan*/  drm_master_internal_acquire (struct drm_device*) ; 
 int /*<<< orphan*/  drm_master_internal_release (struct drm_device*) ; 

int drm_client_modeset_commit(struct drm_client_dev *client)
{
	struct drm_device *dev = client->dev;
	int ret;

	if (!drm_master_internal_acquire(dev))
		return -EBUSY;

	ret = drm_client_modeset_commit_force(client);

	drm_master_internal_release(dev);

	return ret;
}