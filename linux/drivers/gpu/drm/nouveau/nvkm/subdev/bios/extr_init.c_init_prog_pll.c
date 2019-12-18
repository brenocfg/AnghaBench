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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_devinit {int dummy; } ;
struct nvbios_init {TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_devinit* devinit; } ;

/* Variables and functions */
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int nvkm_devinit_pll_set (struct nvkm_devinit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_prog_pll(struct nvbios_init *init, u32 id, u32 freq)
{
	struct nvkm_devinit *devinit = init->subdev->device->devinit;
	if (init_exec(init)) {
		int ret = nvkm_devinit_pll_set(devinit, id, freq);
		if (ret)
			warn("failed to prog pll 0x%08x to %dkHz\n", id, freq);
	}
}