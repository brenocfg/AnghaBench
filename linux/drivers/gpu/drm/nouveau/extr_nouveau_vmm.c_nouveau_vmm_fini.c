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
struct nouveau_vmm {int /*<<< orphan*/ * cli; int /*<<< orphan*/  vmm; int /*<<< orphan*/  svmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_svmm_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_vmm_fini (int /*<<< orphan*/ *) ; 

void
nouveau_vmm_fini(struct nouveau_vmm *vmm)
{
	nouveau_svmm_fini(&vmm->svmm);
	nvif_vmm_fini(&vmm->vmm);
	vmm->cli = NULL;
}