#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv44_mpeg_chan {int inst; struct nv44_mpeg* mpeg; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nv44_mpeg {TYPE_2__ engine; } ;

/* Variables and functions */
 struct nv44_mpeg_chan* nv44_mpeg_chan (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 scalar_t__ nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static int
nv44_mpeg_chan_fini(struct nvkm_object *object, bool suspend)
{

	struct nv44_mpeg_chan *chan = nv44_mpeg_chan(object);
	struct nv44_mpeg *mpeg = chan->mpeg;
	struct nvkm_device *device = mpeg->engine.subdev.device;
	u32 inst = 0x80000000 | (chan->inst >> 4);

	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000000);
	if (nvkm_rd32(device, 0x00b318) == inst)
		nvkm_mask(device, 0x00b318, 0x80000000, 0x00000000);
	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000001);
	return 0;
}