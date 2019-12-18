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
struct nvkm_devinit {int dummy; } ;
struct nvbios_init {int offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_devinit* devinit; } ;

/* Variables and functions */
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int /*<<< orphan*/  init_exec_force (struct nvbios_init*,int) ; 
 int /*<<< orphan*/  nvkm_devinit_meminit (struct nvkm_devinit*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
init_compute_mem(struct nvbios_init *init)
{
	struct nvkm_devinit *devinit = init->subdev->device->devinit;

	trace("COMPUTE_MEM\n");
	init->offset += 1;

	init_exec_force(init, true);
	if (init_exec(init))
		nvkm_devinit_meminit(devinit);
	init_exec_force(init, false);
}