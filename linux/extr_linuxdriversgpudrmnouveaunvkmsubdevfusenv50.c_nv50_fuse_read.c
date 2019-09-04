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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_fuse {int /*<<< orphan*/  lock; TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ nvkm_mask (struct nvkm_device*,int,int,int) ; 
 scalar_t__ nvkm_rd32 (struct nvkm_device*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32
nv50_fuse_read(struct nvkm_fuse *fuse, u32 addr)
{
	struct nvkm_device *device = fuse->subdev.device;
	unsigned long flags;
	u32 fuse_enable, val;

	/* racy if another part of nvkm start writing to this reg */
	spin_lock_irqsave(&fuse->lock, flags);
	fuse_enable = nvkm_mask(device, 0x001084, 0x800, 0x800);
	val = nvkm_rd32(device, 0x021000 + addr);
	nvkm_wr32(device, 0x001084, fuse_enable);
	spin_unlock_irqrestore(&fuse->lock, flags);
	return val;
}