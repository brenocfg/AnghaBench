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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_vmm {int /*<<< orphan*/  mutex; } ;
struct nvkm_vma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvkm_vmm_get_locked (struct nvkm_vmm*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vma**) ; 

int
nvkm_vmm_get(struct nvkm_vmm *vmm, u8 page, u64 size, struct nvkm_vma **pvma)
{
	int ret;
	mutex_lock(&vmm->mutex);
	ret = nvkm_vmm_get_locked(vmm, false, true, false, page, 0, size, pvma);
	mutex_unlock(&vmm->mutex);
	return ret;
}