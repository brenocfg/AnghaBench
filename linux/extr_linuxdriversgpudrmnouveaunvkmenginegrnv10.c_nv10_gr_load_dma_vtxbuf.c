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
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct nv10_gr_chan {struct nv10_gr* gr; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv10_gr {TYPE_3__ base; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int NV04_PGRAPH_FIFO ; 
 int NV10_PGRAPH_CTX_CACHE (int,int) ; 
 int NV10_PGRAPH_CTX_CONTROL ; 
 int NV10_PGRAPH_CTX_SWITCH (int) ; 
 int NV10_PGRAPH_CTX_USER ; 
 int NV10_PGRAPH_FFINTFC_FIFO_PTR ; 
 int NV10_PGRAPH_FFINTFC_ST2 ; 
 int NV10_PGRAPH_FFINTFC_ST2_DH ; 
 int NV10_PGRAPH_FFINTFC_ST2_DL ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv10_gr_load_dma_vtxbuf(struct nv10_gr_chan *chan, int chid, u32 inst)
{
	struct nv10_gr *gr = chan->gr;
	struct nvkm_device *device = gr->base.engine.subdev.device;
	u32 st2, st2_dl, st2_dh, fifo_ptr, fifo[0x60/4];
	u32 ctx_user, ctx_switch[5];
	int i, subchan = -1;

	/* NV10TCL_DMA_VTXBUF (method 0x18c) modifies hidden state
	 * that cannot be restored via MMIO. Do it through the FIFO
	 * instead.
	 */

	/* Look for a celsius object */
	for (i = 0; i < 8; i++) {
		int class = nvkm_rd32(device, NV10_PGRAPH_CTX_CACHE(i, 0)) & 0xfff;

		if (class == 0x56 || class == 0x96 || class == 0x99) {
			subchan = i;
			break;
		}
	}

	if (subchan < 0 || !inst)
		return;

	/* Save the current ctx object */
	ctx_user = nvkm_rd32(device, NV10_PGRAPH_CTX_USER);
	for (i = 0; i < 5; i++)
		ctx_switch[i] = nvkm_rd32(device, NV10_PGRAPH_CTX_SWITCH(i));

	/* Save the FIFO state */
	st2 = nvkm_rd32(device, NV10_PGRAPH_FFINTFC_ST2);
	st2_dl = nvkm_rd32(device, NV10_PGRAPH_FFINTFC_ST2_DL);
	st2_dh = nvkm_rd32(device, NV10_PGRAPH_FFINTFC_ST2_DH);
	fifo_ptr = nvkm_rd32(device, NV10_PGRAPH_FFINTFC_FIFO_PTR);

	for (i = 0; i < ARRAY_SIZE(fifo); i++)
		fifo[i] = nvkm_rd32(device, 0x4007a0 + 4 * i);

	/* Switch to the celsius subchannel */
	for (i = 0; i < 5; i++)
		nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(i),
			nvkm_rd32(device, NV10_PGRAPH_CTX_CACHE(subchan, i)));
	nvkm_mask(device, NV10_PGRAPH_CTX_USER, 0xe000, subchan << 13);

	/* Inject NV10TCL_DMA_VTXBUF */
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_FIFO_PTR, 0);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2,
		0x2c000000 | chid << 20 | subchan << 16 | 0x18c);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2_DL, inst);
	nvkm_mask(device, NV10_PGRAPH_CTX_CONTROL, 0, 0x10000);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000001);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000000);

	/* Restore the FIFO state */
	for (i = 0; i < ARRAY_SIZE(fifo); i++)
		nvkm_wr32(device, 0x4007a0 + 4 * i, fifo[i]);

	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_FIFO_PTR, fifo_ptr);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2, st2);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2_DL, st2_dl);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2_DH, st2_dh);

	/* Restore the current ctx object */
	for (i = 0; i < 5; i++)
		nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(i), ctx_switch[i]);
	nvkm_wr32(device, NV10_PGRAPH_CTX_USER, ctx_user);
}