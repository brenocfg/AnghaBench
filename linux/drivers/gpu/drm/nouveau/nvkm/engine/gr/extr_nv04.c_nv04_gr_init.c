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
struct nvkm_gr {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv04_gr {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV03_PGRAPH_INTR ; 
 int /*<<< orphan*/  NV03_PGRAPH_INTR_EN ; 
 int /*<<< orphan*/  NV04_PGRAPH_BETA_AND ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_CONTROL ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_USER ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_0 ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_1 ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_2 ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_3 ; 
 int /*<<< orphan*/  NV04_PGRAPH_PATTERN_SHAPE ; 
 int /*<<< orphan*/  NV04_PGRAPH_STATE ; 
 int /*<<< orphan*/  NV04_PGRAPH_VALID1 ; 
 int /*<<< orphan*/  NV04_PGRAPH_VALID2 ; 
 struct nv04_gr* nv04_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv04_gr_init(struct nvkm_gr *base)
{
	struct nv04_gr *gr = nv04_gr(base);
	struct nvkm_device *device = gr->base.engine.subdev.device;

	/* Enable PGRAPH interrupts */
	nvkm_wr32(device, NV03_PGRAPH_INTR, 0xFFFFFFFF);
	nvkm_wr32(device, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nvkm_wr32(device, NV04_PGRAPH_VALID1, 0);
	nvkm_wr32(device, NV04_PGRAPH_VALID2, 0);
	/*nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x000001FF);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x001FFFFF);*/
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x1231c000);
	/*1231C000 blob, 001 haiku*/
	/*V_WRITE(NV04_PGRAPH_DEBUG_1, 0xf2d91100);*/
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_1, 0x72111100);
	/*0x72111100 blob , 01 haiku*/
	/*nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x11d5f870);*/
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x11d5f071);
	/*haiku same*/

	/*nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0xfad4ff31);*/
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0xf0d4ff31);
	/*haiku and blob 10d4*/

	nvkm_wr32(device, NV04_PGRAPH_STATE        , 0xFFFFFFFF);
	nvkm_wr32(device, NV04_PGRAPH_CTX_CONTROL  , 0x10000100);
	nvkm_mask(device, NV04_PGRAPH_CTX_USER, 0xff000000, 0x0f000000);

	/* These don't belong here, they're part of a per-channel context */
	nvkm_wr32(device, NV04_PGRAPH_PATTERN_SHAPE, 0x00000000);
	nvkm_wr32(device, NV04_PGRAPH_BETA_AND     , 0xFFFFFFFF);
	return 0;
}