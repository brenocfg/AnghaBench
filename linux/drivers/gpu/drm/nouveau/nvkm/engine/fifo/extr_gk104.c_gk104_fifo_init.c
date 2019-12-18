#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_12__ {TYPE_4__* bar; } ;
struct TYPE_8__ {struct nvkm_device* device; } ;
struct TYPE_9__ {TYPE_1__ subdev; } ;
struct TYPE_10__ {TYPE_2__ engine; } ;
struct gk104_fifo {int pbdma_nr; TYPE_7__* func; TYPE_5__ user; TYPE_3__ base; } ;
struct TYPE_14__ {TYPE_6__* pbdma; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* init_timeout ) (struct gk104_fifo*) ;int /*<<< orphan*/  (* init ) (struct gk104_fifo*) ;} ;
struct TYPE_11__ {int addr; } ;

/* Variables and functions */
 struct gk104_fifo* gk104_fifo (struct nvkm_fifo*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct gk104_fifo*) ; 
 int /*<<< orphan*/  stub2 (struct gk104_fifo*) ; 

__attribute__((used)) static void
gk104_fifo_init(struct nvkm_fifo *base)
{
	struct gk104_fifo *fifo = gk104_fifo(base);
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	int i;

	/* Enable PBDMAs. */
	fifo->func->pbdma->init(fifo);

	/* PBDMA[n] */
	for (i = 0; i < fifo->pbdma_nr; i++) {
		nvkm_mask(device, 0x04013c + (i * 0x2000), 0x10000100, 0x00000000);
		nvkm_wr32(device, 0x040108 + (i * 0x2000), 0xffffffff); /* INTR */
		nvkm_wr32(device, 0x04010c + (i * 0x2000), 0xfffffeff); /* INTREN */
	}

	/* PBDMA[n].HCE */
	for (i = 0; i < fifo->pbdma_nr; i++) {
		nvkm_wr32(device, 0x040148 + (i * 0x2000), 0xffffffff); /* INTR */
		nvkm_wr32(device, 0x04014c + (i * 0x2000), 0xffffffff); /* INTREN */
	}

	nvkm_wr32(device, 0x002254, 0x10000000 | fifo->user.bar->addr >> 12);

	if (fifo->func->pbdma->init_timeout)
		fifo->func->pbdma->init_timeout(fifo);

	nvkm_wr32(device, 0x002100, 0xffffffff);
	nvkm_wr32(device, 0x002140, 0x7fffffff);
}