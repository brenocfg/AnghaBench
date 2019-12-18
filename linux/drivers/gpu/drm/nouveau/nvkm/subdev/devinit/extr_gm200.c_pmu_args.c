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
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nv50_devinit {TYPE_2__ base; } ;

/* Variables and functions */
 scalar_t__ nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,scalar_t__) ; 

__attribute__((used)) static u32
pmu_args(struct nv50_devinit *init, u32 argp, u32 argi)
{
	struct nvkm_device *device = init->base.subdev.device;
	nvkm_wr32(device, 0x10a1c0, argp);
	nvkm_wr32(device, 0x10a1c0, nvkm_rd32(device, 0x10a1c4) + argi);
	return nvkm_rd32(device, 0x10a1c4);
}