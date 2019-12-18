#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_9__ {int ram_size; scalar_t__ family; } ;
struct TYPE_10__ {TYPE_1__ info; } ;
struct TYPE_11__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct TYPE_15__ {unsigned int num_placement; unsigned int num_busy_placement; } ;
struct TYPE_12__ {int num_pages; } ;
struct TYPE_13__ {TYPE_4__ mem; int /*<<< orphan*/  bdev; } ;
struct nouveau_bo {TYPE_8__* busy_placements; TYPE_7__ placement; TYPE_6__* placements; scalar_t__ zeta; TYPE_5__ bo; scalar_t__ mode; } ;
struct TYPE_16__ {unsigned int fpfn; unsigned int lpfn; } ;
struct TYPE_14__ {unsigned int fpfn; unsigned int lpfn; } ;

/* Variables and functions */
 scalar_t__ NV_DEVICE_INFO_V0_CELSIUS ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_VRAM ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_placement_range(struct nouveau_bo *nvbo, uint32_t type)
{
	struct nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	u32 vram_pages = drm->client.device.info.ram_size >> PAGE_SHIFT;
	unsigned i, fpfn, lpfn;

	if (drm->client.device.info.family == NV_DEVICE_INFO_V0_CELSIUS &&
	    nvbo->mode && (type & TTM_PL_FLAG_VRAM) &&
	    nvbo->bo.mem.num_pages < vram_pages / 4) {
		/*
		 * Make sure that the color and depth buffers are handled
		 * by independent memory controller units. Up to a 9x
		 * speed up when alpha-blending and depth-test are enabled
		 * at the same time.
		 */
		if (nvbo->zeta) {
			fpfn = vram_pages / 2;
			lpfn = ~0;
		} else {
			fpfn = 0;
			lpfn = vram_pages / 2;
		}
		for (i = 0; i < nvbo->placement.num_placement; ++i) {
			nvbo->placements[i].fpfn = fpfn;
			nvbo->placements[i].lpfn = lpfn;
		}
		for (i = 0; i < nvbo->placement.num_busy_placement; ++i) {
			nvbo->busy_placements[i].fpfn = fpfn;
			nvbo->busy_placements[i].lpfn = lpfn;
		}
	}
}