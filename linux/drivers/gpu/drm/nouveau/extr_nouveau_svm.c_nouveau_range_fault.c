#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nouveau_svmm {TYPE_1__* mm; int /*<<< orphan*/  mirror; } ;
struct hmm_range {unsigned long pfn_flags_mask; scalar_t__ default_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HMM_RANGE_DEFAULT_TIMEOUT ; 
 long hmm_range_fault (struct hmm_range*,int /*<<< orphan*/ ) ; 
 long hmm_range_register (struct hmm_range*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmm_range_unregister (struct hmm_range*) ; 
 int /*<<< orphan*/  hmm_range_wait_until_valid (struct hmm_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nouveau_range_fault(struct nouveau_svmm *svmm, struct hmm_range *range)
{
	long ret;

	range->default_flags = 0;
	range->pfn_flags_mask = -1UL;

	ret = hmm_range_register(range, &svmm->mirror);
	if (ret) {
		up_read(&svmm->mm->mmap_sem);
		return (int)ret;
	}

	if (!hmm_range_wait_until_valid(range, HMM_RANGE_DEFAULT_TIMEOUT)) {
		up_read(&svmm->mm->mmap_sem);
		return -EBUSY;
	}

	ret = hmm_range_fault(range, 0);
	if (ret <= 0) {
		if (ret == 0)
			ret = -EBUSY;
		up_read(&svmm->mm->mmap_sem);
		hmm_range_unregister(range);
		return ret;
	}
	return 0;
}