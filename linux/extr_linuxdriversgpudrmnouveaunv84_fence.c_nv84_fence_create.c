#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int uevent; int /*<<< orphan*/  context_del; int /*<<< orphan*/  context_new; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; int /*<<< orphan*/  (* dtor ) (struct nouveau_drm*) ;} ;
struct nv84_fence_priv {int /*<<< orphan*/  bo; int /*<<< orphan*/  mutex; TYPE_1__ base; } ;
struct TYPE_9__ {int nr; } ;
struct TYPE_7__ {scalar_t__ ram_size; } ;
struct TYPE_8__ {TYPE_2__ info; } ;
struct TYPE_10__ {TYPE_3__ device; } ;
struct nouveau_drm {TYPE_4__ chan; TYPE_5__ client; struct nv84_fence_priv* fence; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TTM_PL_FLAG_TT ; 
 int TTM_PL_FLAG_UNCACHED ; 
 int TTM_PL_FLAG_VRAM ; 
 struct nv84_fence_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nouveau_bo_map (int /*<<< orphan*/ ) ; 
 int nouveau_bo_new (TYPE_5__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nouveau_bo_pin (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv84_fence_context_del ; 
 int /*<<< orphan*/  nv84_fence_context_new ; 
 int /*<<< orphan*/  nv84_fence_destroy (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nv84_fence_resume ; 
 int /*<<< orphan*/  nv84_fence_suspend ; 

int
nv84_fence_create(struct nouveau_drm *drm)
{
	struct nv84_fence_priv *priv;
	u32 domain;
	int ret;

	priv = drm->fence = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->base.dtor = nv84_fence_destroy;
	priv->base.suspend = nv84_fence_suspend;
	priv->base.resume = nv84_fence_resume;
	priv->base.context_new = nv84_fence_context_new;
	priv->base.context_del = nv84_fence_context_del;

	priv->base.uevent = true;

	mutex_init(&priv->mutex);

	/* Use VRAM if there is any ; otherwise fallback to system memory */
	domain = drm->client.device.info.ram_size != 0 ? TTM_PL_FLAG_VRAM :
			 /*
			  * fences created in sysmem must be non-cached or we
			  * will lose CPU/GPU coherency!
			  */
			 TTM_PL_FLAG_TT | TTM_PL_FLAG_UNCACHED;
	ret = nouveau_bo_new(&drm->client, 16 * drm->chan.nr, 0,
			     domain, 0, 0, NULL, NULL, &priv->bo);
	if (ret == 0) {
		ret = nouveau_bo_pin(priv->bo, domain, false);
		if (ret == 0) {
			ret = nouveau_bo_map(priv->bo);
			if (ret)
				nouveau_bo_unpin(priv->bo);
		}
		if (ret)
			nouveau_bo_ref(NULL, &priv->bo);
	}

	if (ret)
		nv84_fence_destroy(drm);
	return ret;
}