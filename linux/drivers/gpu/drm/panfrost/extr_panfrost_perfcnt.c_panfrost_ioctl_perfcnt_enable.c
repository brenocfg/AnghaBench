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
struct panfrost_perfcnt {int /*<<< orphan*/  lock; } ;
struct panfrost_file_priv {int dummy; } ;
struct panfrost_device {struct panfrost_perfcnt* perfcnt; } ;
struct drm_panfrost_perfcnt_enable {int counterset; scalar_t__ enable; } ;
struct drm_file {struct panfrost_file_priv* driver_priv; } ;
struct drm_device {struct panfrost_device* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ panfrost_model_is_bifrost (struct panfrost_device*) ; 
 int panfrost_perfcnt_disable_locked (struct panfrost_device*,struct panfrost_file_priv*) ; 
 int panfrost_perfcnt_enable_locked (struct panfrost_device*,struct panfrost_file_priv*,int) ; 
 int panfrost_unstable_ioctl_check () ; 

int panfrost_ioctl_perfcnt_enable(struct drm_device *dev, void *data,
				  struct drm_file *file_priv)
{
	struct panfrost_file_priv *pfile = file_priv->driver_priv;
	struct panfrost_device *pfdev = dev->dev_private;
	struct panfrost_perfcnt *perfcnt = pfdev->perfcnt;
	struct drm_panfrost_perfcnt_enable *req = data;
	int ret;

	ret = panfrost_unstable_ioctl_check();
	if (ret)
		return ret;

	/* Only Bifrost GPUs have 2 set of counters. */
	if (req->counterset > (panfrost_model_is_bifrost(pfdev) ? 1 : 0))
		return -EINVAL;

	mutex_lock(&perfcnt->lock);
	if (req->enable)
		ret = panfrost_perfcnt_enable_locked(pfdev, pfile,
						     req->counterset);
	else
		ret = panfrost_perfcnt_disable_locked(pfdev, pfile);
	mutex_unlock(&perfcnt->lock);

	return ret;
}