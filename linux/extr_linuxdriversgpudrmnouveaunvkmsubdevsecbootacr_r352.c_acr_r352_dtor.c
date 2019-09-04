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
struct nvkm_acr {scalar_t__ boot_falcon; } ;
struct acr_r352 {int /*<<< orphan*/  ls_blob; int /*<<< orphan*/  load_blob; struct acr_r352* hsbl_blob; struct acr_r352* hsbl_unload_blob; int /*<<< orphan*/  unload_blob; } ;

/* Variables and functions */
 scalar_t__ NVKM_SECBOOT_FALCON_PMU ; 
 struct acr_r352* acr_r352 (struct nvkm_acr*) ; 
 int /*<<< orphan*/  kfree (struct acr_r352*) ; 
 int /*<<< orphan*/  nvkm_gpuobj_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
acr_r352_dtor(struct nvkm_acr *_acr)
{
	struct acr_r352 *acr = acr_r352(_acr);

	nvkm_gpuobj_del(&acr->unload_blob);

	if (_acr->boot_falcon != NVKM_SECBOOT_FALCON_PMU)
		kfree(acr->hsbl_unload_blob);
	kfree(acr->hsbl_blob);
	nvkm_gpuobj_del(&acr->load_blob);
	nvkm_gpuobj_del(&acr->ls_blob);

	kfree(acr);
}