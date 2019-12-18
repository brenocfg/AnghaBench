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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_memory {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gk104_fifo {TYPE_3__ base; } ;

/* Variables and functions */
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_memory_addr (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tu102_fifo_runlist_commit(struct gk104_fifo *fifo, int runl,
			  struct nvkm_memory *mem, int nr)
{
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	u64 addr = nvkm_memory_addr(mem);
	/*XXX: target? */

	nvkm_wr32(device, 0x002b00 + (runl * 0x10), lower_32_bits(addr));
	nvkm_wr32(device, 0x002b04 + (runl * 0x10), upper_32_bits(addr));
	nvkm_wr32(device, 0x002b08 + (runl * 0x10), nr);

	/*XXX: how to wait? can you even wait? */
}