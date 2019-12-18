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
struct nvkm_ram {int dummy; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; } ;
struct TYPE_6__ {TYPE_2__* fb; } ;
struct nv50_ram {int /*<<< orphan*/  hwsq; TYPE_3__ base; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 struct nv50_ram* nv50_ram (struct nvkm_ram*) ; 
 int /*<<< orphan*/  nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ram_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_ram_prog(struct nvkm_ram *base)
{
	struct nv50_ram *ram = nv50_ram(base);
	struct nvkm_device *device = ram->base.fb->subdev.device;
	ram_exec(&ram->hwsq, nvkm_boolopt(device->cfgopt, "NvMemExec", true));
	return 0;
}