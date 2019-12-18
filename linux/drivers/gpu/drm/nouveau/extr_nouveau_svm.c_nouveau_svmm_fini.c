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
struct nouveau_svmm {int /*<<< orphan*/  mirror; } ;

/* Variables and functions */
 int /*<<< orphan*/  hmm_mirror_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nouveau_svmm*) ; 

void
nouveau_svmm_fini(struct nouveau_svmm **psvmm)
{
	struct nouveau_svmm *svmm = *psvmm;
	if (svmm) {
		hmm_mirror_unregister(&svmm->mirror);
		kfree(*psvmm);
		*psvmm = NULL;
	}
}