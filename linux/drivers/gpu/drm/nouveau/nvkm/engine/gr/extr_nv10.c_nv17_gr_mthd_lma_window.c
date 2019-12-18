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
typedef  int u32 ;
struct pipe_state {int* pipe_0x0200; int* pipe_0x4400; } ;
struct nvkm_gr {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_7__ {TYPE_2__* engine; } ;
struct nv10_gr_chan {int* lma_window; struct pipe_state pipe_state; TYPE_4__* gr; TYPE_3__ object; } ;
struct TYPE_8__ {struct nvkm_gr base; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV10_PGRAPH_PIPE_ADDRESS ; 
 int /*<<< orphan*/  NV10_PGRAPH_PIPE_DATA ; 
 int /*<<< orphan*/  NV10_PGRAPH_XFMODE0 ; 
 int /*<<< orphan*/  NV10_PGRAPH_XFMODE1 ; 
 int /*<<< orphan*/  PIPE_RESTORE (struct nvkm_device*,int*,int) ; 
 int /*<<< orphan*/  PIPE_SAVE (struct nvkm_device*,int*,int) ; 
 int /*<<< orphan*/  nv04_gr_idle (struct nvkm_gr*) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nv17_gr_mthd_lma_window(struct nv10_gr_chan *chan, u32 mthd, u32 data)
{
	struct nvkm_device *device = chan->object.engine->subdev.device;
	struct nvkm_gr *gr = &chan->gr->base;
	struct pipe_state *pipe = &chan->pipe_state;
	u32 pipe_0x0040[1], pipe_0x64c0[8], pipe_0x6a80[3], pipe_0x6ab0[3];
	u32 xfmode0, xfmode1;
	int i;

	chan->lma_window[(mthd - 0x1638) / 4] = data;

	if (mthd != 0x1644)
		return;

	nv04_gr_idle(gr);

	PIPE_SAVE(device, pipe_0x0040, 0x0040);
	PIPE_SAVE(device, pipe->pipe_0x0200, 0x0200);

	PIPE_RESTORE(device, chan->lma_window, 0x6790);

	nv04_gr_idle(gr);

	xfmode0 = nvkm_rd32(device, NV10_PGRAPH_XFMODE0);
	xfmode1 = nvkm_rd32(device, NV10_PGRAPH_XFMODE1);

	PIPE_SAVE(device, pipe->pipe_0x4400, 0x4400);
	PIPE_SAVE(device, pipe_0x64c0, 0x64c0);
	PIPE_SAVE(device, pipe_0x6ab0, 0x6ab0);
	PIPE_SAVE(device, pipe_0x6a80, 0x6a80);

	nv04_gr_idle(gr);

	nvkm_wr32(device, NV10_PGRAPH_XFMODE0, 0x10000000);
	nvkm_wr32(device, NV10_PGRAPH_XFMODE1, 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x000064c0);
	for (i = 0; i < 4; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x3f800000);
	for (i = 0; i < 4; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00006ab0);
	for (i = 0; i < 3; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x3f800000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00006a80);
	for (i = 0; i < 3; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00000040);
	nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000008);

	PIPE_RESTORE(device, pipe->pipe_0x0200, 0x0200);

	nv04_gr_idle(gr);

	PIPE_RESTORE(device, pipe_0x0040, 0x0040);

	nvkm_wr32(device, NV10_PGRAPH_XFMODE0, xfmode0);
	nvkm_wr32(device, NV10_PGRAPH_XFMODE1, xfmode1);

	PIPE_RESTORE(device, pipe_0x64c0, 0x64c0);
	PIPE_RESTORE(device, pipe_0x6ab0, 0x6ab0);
	PIPE_RESTORE(device, pipe_0x6a80, 0x6a80);
	PIPE_RESTORE(device, pipe->pipe_0x4400, 0x4400);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x000000c0);
	nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nv04_gr_idle(gr);
}