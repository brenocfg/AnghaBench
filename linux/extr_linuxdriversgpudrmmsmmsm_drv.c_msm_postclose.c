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
struct msm_file_private {int dummy; } ;
struct msm_drm_private {struct msm_file_private* lastctx; } ;
struct drm_file {struct msm_file_private* driver_priv; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_close (struct msm_file_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msm_postclose(struct drm_device *dev, struct drm_file *file)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_file_private *ctx = file->driver_priv;

	mutex_lock(&dev->struct_mutex);
	if (ctx == priv->lastctx)
		priv->lastctx = NULL;
	mutex_unlock(&dev->struct_mutex);

	context_close(ctx);
}