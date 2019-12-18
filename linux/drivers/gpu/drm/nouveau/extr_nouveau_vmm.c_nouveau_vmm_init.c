#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nouveau_vmm {struct nouveau_cli* cli; int /*<<< orphan*/  vmm; } ;
struct nouveau_cli {int /*<<< orphan*/  mmu; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int nvif_vmm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nouveau_vmm_init(struct nouveau_cli *cli, s32 oclass, struct nouveau_vmm *vmm)
{
	int ret = nvif_vmm_init(&cli->mmu, oclass, false, PAGE_SIZE, 0, NULL, 0,
				&vmm->vmm);
	if (ret)
		return ret;

	vmm->cli = cli;
	return 0;
}