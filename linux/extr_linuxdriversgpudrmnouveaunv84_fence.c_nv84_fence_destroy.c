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
struct nv84_fence_priv {scalar_t__ bo; } ;
struct nouveau_drm {struct nv84_fence_priv* fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nv84_fence_priv*) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (scalar_t__) ; 

__attribute__((used)) static void
nv84_fence_destroy(struct nouveau_drm *drm)
{
	struct nv84_fence_priv *priv = drm->fence;
	nouveau_bo_unmap(priv->bo);
	if (priv->bo)
		nouveau_bo_unpin(priv->bo);
	nouveau_bo_ref(NULL, &priv->bo);
	drm->fence = NULL;
	kfree(priv);
}