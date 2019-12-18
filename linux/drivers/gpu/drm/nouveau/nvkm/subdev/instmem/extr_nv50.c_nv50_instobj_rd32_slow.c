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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_memory {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv50_instobj {int /*<<< orphan*/  ram; struct nv50_instmem* imem; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__ subdev; } ;
struct nv50_instmem {int addr; TYPE_2__ base; } ;

/* Variables and functions */
 struct nv50_instobj* nv50_instobj (struct nvkm_memory*) ; 
 int nvkm_memory_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32
nv50_instobj_rd32_slow(struct nvkm_memory *memory, u64 offset)
{
	struct nv50_instobj *iobj = nv50_instobj(memory);
	struct nv50_instmem *imem = iobj->imem;
	struct nvkm_device *device = imem->base.subdev.device;
	u64 base = (nvkm_memory_addr(iobj->ram) + offset) & 0xffffff00000ULL;
	u64 addr = (nvkm_memory_addr(iobj->ram) + offset) & 0x000000fffffULL;
	u32 data;
	unsigned long flags;

	spin_lock_irqsave(&imem->base.lock, flags);
	if (unlikely(imem->addr != base)) {
		nvkm_wr32(device, 0x001700, base >> 16);
		imem->addr = base;
	}
	data = nvkm_rd32(device, 0x700000 + addr);
	spin_unlock_irqrestore(&imem->base.lock, flags);
	return data;
}