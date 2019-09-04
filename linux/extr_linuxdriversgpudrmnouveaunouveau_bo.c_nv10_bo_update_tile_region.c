#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_fb_tile {scalar_t__ pitch; } ;
struct TYPE_5__ {struct nvkm_fb_tile* region; } ;
struct nvkm_fb {TYPE_2__ tile; } ;
struct nouveau_drm_tile {int /*<<< orphan*/  fence; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {struct nouveau_drm_tile* reg; } ;
struct nouveau_drm {TYPE_1__ client; TYPE_3__ tile; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fence_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_fb_tile_fini (struct nvkm_fb*,int,struct nvkm_fb_tile*) ; 
 int /*<<< orphan*/  nvkm_fb_tile_init (struct nvkm_fb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_fb_tile*) ; 
 int /*<<< orphan*/  nvkm_fb_tile_prog (struct nvkm_fb*,int,struct nvkm_fb_tile*) ; 
 struct nvkm_fb* nvxx_fb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv10_bo_update_tile_region(struct drm_device *dev, struct nouveau_drm_tile *reg,
			   u32 addr, u32 size, u32 pitch, u32 flags)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	int i = reg - drm->tile.reg;
	struct nvkm_fb *fb = nvxx_fb(&drm->client.device);
	struct nvkm_fb_tile *tile = &fb->tile.region[i];

	nouveau_fence_unref(&reg->fence);

	if (tile->pitch)
		nvkm_fb_tile_fini(fb, i, tile);

	if (pitch)
		nvkm_fb_tile_init(fb, i, addr, size, pitch, flags, tile);

	nvkm_fb_tile_prog(fb, i, tile);
}