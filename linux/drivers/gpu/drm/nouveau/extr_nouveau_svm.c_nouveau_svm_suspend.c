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
struct nouveau_svm {int dummy; } ;
struct nouveau_drm {struct nouveau_svm* svm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_svm_fault_buffer_fini (struct nouveau_svm*,int /*<<< orphan*/ ) ; 

void
nouveau_svm_suspend(struct nouveau_drm *drm)
{
	struct nouveau_svm *svm = drm->svm;
	if (svm)
		nouveau_svm_fault_buffer_fini(svm, 0);
}