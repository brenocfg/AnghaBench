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
struct nvkm_fb {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct nv50_fb {int r100c08; TYPE_3__* func; TYPE_2__ base; } ;
struct TYPE_6__ {int trap; } ;

/* Variables and functions */
 struct nv50_fb* nv50_fb (struct nvkm_fb*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv50_fb_init(struct nvkm_fb *base)
{
	struct nv50_fb *fb = nv50_fb(base);
	struct nvkm_device *device = fb->base.subdev.device;

	/* Not a clue what this is exactly.  Without pointing it at a
	 * scratch page, VRAM->GART blits with M2MF (as in DDX DFS)
	 * cause IOMMU "read from address 0" errors (rh#561267)
	 */
	nvkm_wr32(device, 0x100c08, fb->r100c08 >> 8);

	/* This is needed to get meaningful information from 100c90
	 * on traps. No idea what these values mean exactly. */
	nvkm_wr32(device, 0x100c90, fb->func->trap);
}