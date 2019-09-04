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
struct drm_file {int authenticated; TYPE_1__* master; } ;
struct drm_device {int /*<<< orphan*/  master_mutex; } ;
struct drm_auth {int /*<<< orphan*/  magic; } ;
struct TYPE_2__ {int /*<<< orphan*/  magic_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct drm_file* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_authmagic(struct drm_device *dev, void *data,
		  struct drm_file *file_priv)
{
	struct drm_auth *auth = data;
	struct drm_file *file;

	DRM_DEBUG("%u\n", auth->magic);

	mutex_lock(&dev->master_mutex);
	file = idr_find(&file_priv->master->magic_map, auth->magic);
	if (file) {
		file->authenticated = 1;
		idr_replace(&file_priv->master->magic_map, NULL, auth->magic);
	}
	mutex_unlock(&dev->master_mutex);

	return file ? 0 : -EINVAL;
}