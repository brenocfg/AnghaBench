#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {struct nvkm_fifo* fifo; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_clk {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_fifo_start (struct nvkm_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 

void
gt215_clk_post(struct nvkm_clk *clk, unsigned long *flags)
{
	struct nvkm_device *device = clk->subdev.device;
	struct nvkm_fifo *fifo = device->fifo;

	if (fifo && flags)
		nvkm_fifo_start(fifo, flags);

	nvkm_mask(device, 0x002504, 0x00000001, 0x00000000);
	nvkm_mask(device, 0x020060, 0x00070000, 0x00040000);
}