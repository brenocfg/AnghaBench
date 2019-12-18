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
struct msm_fence_context {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  event; int /*<<< orphan*/  context; int /*<<< orphan*/  name; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct msm_fence_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct msm_fence_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

struct msm_fence_context *
msm_fence_context_alloc(struct drm_device *dev, const char *name)
{
	struct msm_fence_context *fctx;

	fctx = kzalloc(sizeof(*fctx), GFP_KERNEL);
	if (!fctx)
		return ERR_PTR(-ENOMEM);

	fctx->dev = dev;
	strncpy(fctx->name, name, sizeof(fctx->name));
	fctx->context = dma_fence_context_alloc(1);
	init_waitqueue_head(&fctx->event);
	spin_lock_init(&fctx->spinlock);

	return fctx;
}