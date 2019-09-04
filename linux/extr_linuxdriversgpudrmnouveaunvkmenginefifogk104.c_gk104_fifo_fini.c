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
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  work; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gk104_fifo {TYPE_4__ recover; TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct gk104_fifo* gk104_fifo (struct nvkm_fifo*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 

__attribute__((used)) static void
gk104_fifo_fini(struct nvkm_fifo *base)
{
	struct gk104_fifo *fifo = gk104_fifo(base);
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	flush_work(&fifo->recover.work);
	/* allow mmu fault interrupts, even when we're not using fifo */
	nvkm_mask(device, 0x002140, 0x10000000, 0x10000000);
}