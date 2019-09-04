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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_subdev {TYPE_2__* device; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_pmuR {int /*<<< orphan*/  init_addr_pmu; int /*<<< orphan*/  args_addr_pmu; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data_addr; int /*<<< orphan*/  data_addr_pmu; int /*<<< orphan*/  code_size; int /*<<< orphan*/  code_addr; int /*<<< orphan*/  code_addr_pmu; int /*<<< orphan*/  boot_size; int /*<<< orphan*/  boot_addr; int /*<<< orphan*/  boot_addr_pmu; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct nv50_devinit {TYPE_1__ base; } ;
struct TYPE_4__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvbios_pmuRm (struct nvkm_bios*,int /*<<< orphan*/ ,struct nvbios_pmuR*) ; 
 int /*<<< orphan*/  pmu_code (struct nv50_devinit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmu_data (struct nv50_devinit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmu_exec (struct nv50_devinit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmu_load(struct nv50_devinit *init, u8 type, bool post,
	 u32 *init_addr_pmu, u32 *args_addr_pmu)
{
	struct nvkm_subdev *subdev = &init->base.subdev;
	struct nvkm_bios *bios = subdev->device->bios;
	struct nvbios_pmuR pmu;

	if (!nvbios_pmuRm(bios, type, &pmu))
		return -EINVAL;

	if (!post)
		return 0;

	pmu_code(init, pmu.boot_addr_pmu, pmu.boot_addr, pmu.boot_size, false);
	pmu_code(init, pmu.code_addr_pmu, pmu.code_addr, pmu.code_size, true);
	pmu_data(init, pmu.data_addr_pmu, pmu.data_addr, pmu.data_size);

	if (init_addr_pmu) {
		*init_addr_pmu = pmu.init_addr_pmu;
		*args_addr_pmu = pmu.args_addr_pmu;
		return 0;
	}

	return pmu_exec(init, pmu.init_addr_pmu), 0;
}