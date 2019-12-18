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
struct msm_file_private {int /*<<< orphan*/ * aspace; } ;
struct msm_drm_private {TYPE_1__* gpu; } ;
struct drm_file {struct msm_file_private* driver_priv; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * aspace; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct msm_file_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_submitqueue_init (struct drm_device*,struct msm_file_private*) ; 

__attribute__((used)) static int context_init(struct drm_device *dev, struct drm_file *file)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_file_private *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	msm_submitqueue_init(dev, ctx);

	ctx->aspace = priv->gpu ? priv->gpu->aspace : NULL;
	file->driver_priv = ctx;

	return 0;
}