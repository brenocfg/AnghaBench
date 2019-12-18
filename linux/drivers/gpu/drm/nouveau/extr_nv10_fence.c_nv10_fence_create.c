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
struct TYPE_2__ {int /*<<< orphan*/  context_del; int /*<<< orphan*/  context_new; int /*<<< orphan*/  dtor; } ;
struct nv10_fence_priv {int /*<<< orphan*/  lock; TYPE_1__ base; } ;
struct nouveau_drm {struct nv10_fence_priv* fence; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv10_fence_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv10_fence_context_del ; 
 int /*<<< orphan*/  nv10_fence_context_new ; 
 int /*<<< orphan*/  nv10_fence_destroy ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nv10_fence_create(struct nouveau_drm *drm)
{
	struct nv10_fence_priv *priv;

	priv = drm->fence = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->base.dtor = nv10_fence_destroy;
	priv->base.context_new = nv10_fence_context_new;
	priv->base.context_del = nv10_fence_context_del;
	spin_lock_init(&priv->lock);
	return 0;
}