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
struct nvif_mclass {int /*<<< orphan*/  oclass; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct nouveau_svm {int /*<<< orphan*/  inst; int /*<<< orphan*/  mutex; struct nouveau_drm* drm; } ;
struct TYPE_4__ {scalar_t__ family; } ;
struct TYPE_5__ {int /*<<< orphan*/  object; TYPE_1__ info; } ;
struct TYPE_6__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; struct nouveau_svm* svm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  MAXWELL_FAULT_BUFFER_A 129 
 scalar_t__ NV_DEVICE_INFO_V0_PASCAL ; 
 int /*<<< orphan*/  SVM_DBG (struct nouveau_svm*,char*) ; 
#define  VOLTA_FAULT_BUFFER_A 128 
 struct nouveau_svm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nouveau_svm_fault_buffer_ctor (struct nouveau_svm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_svm_fini (struct nouveau_drm*) ; 
 int nvif_mclass (int /*<<< orphan*/ *,struct nvif_mclass const*) ; 

void
nouveau_svm_init(struct nouveau_drm *drm)
{
	static const struct nvif_mclass buffers[] = {
		{   VOLTA_FAULT_BUFFER_A, 0 },
		{ MAXWELL_FAULT_BUFFER_A, 0 },
		{}
	};
	struct nouveau_svm *svm;
	int ret;

	/* Disable on Volta and newer until channel recovery is fixed,
	 * otherwise clients will have a trivial way to trash the GPU
	 * for everyone.
	 */
	if (drm->client.device.info.family > NV_DEVICE_INFO_V0_PASCAL)
		return;

	if (!(drm->svm = svm = kzalloc(sizeof(*drm->svm), GFP_KERNEL)))
		return;

	drm->svm->drm = drm;
	mutex_init(&drm->svm->mutex);
	INIT_LIST_HEAD(&drm->svm->inst);

	ret = nvif_mclass(&drm->client.device.object, buffers);
	if (ret < 0) {
		SVM_DBG(svm, "No supported fault buffer class");
		nouveau_svm_fini(drm);
		return;
	}

	ret = nouveau_svm_fault_buffer_ctor(svm, buffers[ret].oclass, 0);
	if (ret) {
		nouveau_svm_fini(drm);
		return;
	}

	SVM_DBG(svm, "Initialised");
}