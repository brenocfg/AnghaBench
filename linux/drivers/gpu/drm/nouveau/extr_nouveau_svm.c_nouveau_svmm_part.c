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
struct nouveau_svmm {TYPE_3__* vmm; } ;
struct nouveau_ivmm {int /*<<< orphan*/  head; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {TYPE_2__* cli; } ;
struct TYPE_6__ {TYPE_1__* drm; } ;
struct TYPE_5__ {TYPE_4__* svm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nouveau_ivmm*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nouveau_ivmm* nouveau_ivmm_find (TYPE_4__*,int /*<<< orphan*/ ) ; 

void
nouveau_svmm_part(struct nouveau_svmm *svmm, u64 inst)
{
	struct nouveau_ivmm *ivmm;
	if (svmm) {
		mutex_lock(&svmm->vmm->cli->drm->svm->mutex);
		ivmm = nouveau_ivmm_find(svmm->vmm->cli->drm->svm, inst);
		if (ivmm) {
			list_del(&ivmm->head);
			kfree(ivmm);
		}
		mutex_unlock(&svmm->vmm->cli->drm->svm->mutex);
	}
}