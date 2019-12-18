#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct nouveau_svmm {TYPE_4__* vmm; } ;
struct nouveau_ivmm {int /*<<< orphan*/  head; int /*<<< orphan*/  inst; struct nouveau_svmm* svmm; } ;
struct TYPE_8__ {TYPE_3__* cli; } ;
struct TYPE_7__ {TYPE_2__* drm; } ;
struct TYPE_6__ {TYPE_1__* svm; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nouveau_ivmm* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
nouveau_svmm_join(struct nouveau_svmm *svmm, u64 inst)
{
	struct nouveau_ivmm *ivmm;
	if (svmm) {
		if (!(ivmm = kmalloc(sizeof(*ivmm), GFP_KERNEL)))
			return -ENOMEM;
		ivmm->svmm = svmm;
		ivmm->inst = inst;

		mutex_lock(&svmm->vmm->cli->drm->svm->mutex);
		list_add(&ivmm->head, &svmm->vmm->cli->drm->svm->inst);
		mutex_unlock(&svmm->vmm->cli->drm->svm->mutex);
	}
	return 0;
}