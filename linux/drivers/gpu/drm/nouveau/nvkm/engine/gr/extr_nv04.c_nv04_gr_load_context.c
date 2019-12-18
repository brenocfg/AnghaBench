#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvkm_device {int dummy; } ;
struct nv04_gr_chan {int* nv04; TYPE_4__* gr; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct TYPE_8__ {TYPE_3__ base; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_CONTROL ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_USER ; 
 int /*<<< orphan*/  NV04_PGRAPH_FFINTFC_ST2 ; 
 int /*<<< orphan*/ * nv04_gr_ctx_regs ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv04_gr_load_context(struct nv04_gr_chan *chan, int chid)
{
	struct nvkm_device *device = chan->gr->base.engine.subdev.device;
	int i;

	for (i = 0; i < ARRAY_SIZE(nv04_gr_ctx_regs); i++)
		nvkm_wr32(device, nv04_gr_ctx_regs[i], chan->nv04[i]);

	nvkm_wr32(device, NV04_PGRAPH_CTX_CONTROL, 0x10010100);
	nvkm_mask(device, NV04_PGRAPH_CTX_USER, 0xff000000, chid << 24);
	nvkm_mask(device, NV04_PGRAPH_FFINTFC_ST2, 0xfff00000, 0x00000000);
	return 0;
}