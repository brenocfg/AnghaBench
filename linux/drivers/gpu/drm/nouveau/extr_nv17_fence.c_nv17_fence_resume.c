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
struct nv10_fence_priv {int /*<<< orphan*/  sequence; int /*<<< orphan*/  bo; } ;
struct nouveau_drm {struct nv10_fence_priv* fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bo_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nv17_fence_resume(struct nouveau_drm *drm)
{
	struct nv10_fence_priv *priv = drm->fence;

	nouveau_bo_wr32(priv->bo, 0, priv->sequence);
}