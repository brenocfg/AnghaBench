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
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_10__ {TYPE_4__* bar; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;
struct TYPE_8__ {TYPE_2__ engine; } ;
struct gf100_fifo {int pbdma_nr; TYPE_5__ user; TYPE_3__ base; } ;
struct TYPE_9__ {int addr; } ;

/* Variables and functions */
 struct gf100_fifo* gf100_fifo (struct nvkm_fifo*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_fifo_init(struct nvkm_fifo *base)
{
	struct gf100_fifo *fifo = gf100_fifo(base);
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	int i;

	/* Enable PBDMAs. */
	nvkm_wr32(device, 0x000204, (1 << fifo->pbdma_nr) - 1);
	nvkm_wr32(device, 0x002204, (1 << fifo->pbdma_nr) - 1);

	/* Assign engines to PBDMAs. */
	if (fifo->pbdma_nr >= 3) {
		nvkm_wr32(device, 0x002208, ~(1 << 0)); /* PGRAPH */
		nvkm_wr32(device, 0x00220c, ~(1 << 1)); /* PVP */
		nvkm_wr32(device, 0x002210, ~(1 << 1)); /* PMSPP */
		nvkm_wr32(device, 0x002214, ~(1 << 1)); /* PMSVLD */
		nvkm_wr32(device, 0x002218, ~(1 << 2)); /* PCE0 */
		nvkm_wr32(device, 0x00221c, ~(1 << 1)); /* PCE1 */
	}

	/* PBDMA[n] */
	for (i = 0; i < fifo->pbdma_nr; i++) {
		nvkm_mask(device, 0x04013c + (i * 0x2000), 0x10000100, 0x00000000);
		nvkm_wr32(device, 0x040108 + (i * 0x2000), 0xffffffff); /* INTR */
		nvkm_wr32(device, 0x04010c + (i * 0x2000), 0xfffffeff); /* INTREN */
	}

	nvkm_mask(device, 0x002200, 0x00000001, 0x00000001);
	nvkm_wr32(device, 0x002254, 0x10000000 | fifo->user.bar->addr >> 12);

	nvkm_wr32(device, 0x002100, 0xffffffff);
	nvkm_wr32(device, 0x002140, 0x7fffffff);
	nvkm_wr32(device, 0x002628, 0x00000001); /* ENGINE_INTR_EN */
}