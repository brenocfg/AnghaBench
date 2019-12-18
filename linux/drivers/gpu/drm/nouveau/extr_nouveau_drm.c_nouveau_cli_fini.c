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
struct nouveau_cli {TYPE_2__* drm; int /*<<< orphan*/  base; int /*<<< orphan*/  device; int /*<<< orphan*/  mmu; int /*<<< orphan*/  vmm; int /*<<< orphan*/  svm; int /*<<< orphan*/  worker; int /*<<< orphan*/  work; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ master; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_vmm_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_client_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_device_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_mmu_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usif_client_fini (struct nouveau_cli*) ; 

__attribute__((used)) static void
nouveau_cli_fini(struct nouveau_cli *cli)
{
	/* All our channels are dead now, which means all the fences they
	 * own are signalled, and all callback functions have been called.
	 *
	 * So, after flushing the workqueue, there should be nothing left.
	 */
	flush_work(&cli->work);
	WARN_ON(!list_empty(&cli->worker));

	usif_client_fini(cli);
	nouveau_vmm_fini(&cli->svm);
	nouveau_vmm_fini(&cli->vmm);
	nvif_mmu_fini(&cli->mmu);
	nvif_device_fini(&cli->device);
	mutex_lock(&cli->drm->master.lock);
	nvif_client_fini(&cli->base);
	mutex_unlock(&cli->drm->master.lock);
}