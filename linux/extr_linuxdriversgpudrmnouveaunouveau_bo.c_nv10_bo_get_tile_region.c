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
struct nouveau_drm_tile {int used; int /*<<< orphan*/  fence; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct nouveau_drm_tile* reg; } ;
struct nouveau_drm {TYPE_1__ tile; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 scalar_t__ nouveau_fence_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nouveau_drm_tile *
nv10_bo_get_tile_region(struct drm_device *dev, int i)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_drm_tile *tile = &drm->tile.reg[i];

	spin_lock(&drm->tile.lock);

	if (!tile->used &&
	    (!tile->fence || nouveau_fence_done(tile->fence)))
		tile->used = true;
	else
		tile = NULL;

	spin_unlock(&drm->tile.lock);
	return tile;
}