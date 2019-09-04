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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_device {int dummy; } ;
struct nvbios_init {TYPE_1__* subdev; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;

/* Variables and functions */
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int /*<<< orphan*/  init_nvreg (struct nvbios_init*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_wr32(struct nvbios_init *init, u32 reg, u32 val)
{
	struct nvkm_device *device = init->subdev->device;
	reg = init_nvreg(init, reg);
	if (reg != ~0 && init_exec(init))
		nvkm_wr32(device, reg, val);
}