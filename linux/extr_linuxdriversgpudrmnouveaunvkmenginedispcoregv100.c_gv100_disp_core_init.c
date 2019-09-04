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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct nv50_disp_chan {int /*<<< orphan*/  push; TYPE_3__* disp; } ;
struct TYPE_4__ {struct nvkm_subdev subdev; } ;
struct TYPE_5__ {TYPE_1__ engine; } ;
struct TYPE_6__ {TYPE_2__ base; } ;

/* Variables and functions */
 int gv100_disp_core_idle (struct nv50_disp_chan*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gv100_disp_core_init(struct nv50_disp_chan *chan)
{
	struct nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;

	nvkm_wr32(device, 0x610b24, lower_32_bits(chan->push));
	nvkm_wr32(device, 0x610b20, upper_32_bits(chan->push));
	nvkm_wr32(device, 0x610b28, 0x00000001);
	nvkm_wr32(device, 0x610b2c, 0x00000040);

	nvkm_mask(device, 0x6104e0, 0x00000010, 0x00000010);
	nvkm_wr32(device, 0x680000, 0x00000000);
	nvkm_wr32(device, 0x6104e0, 0x00000013);
	return gv100_disp_core_idle(chan);
}