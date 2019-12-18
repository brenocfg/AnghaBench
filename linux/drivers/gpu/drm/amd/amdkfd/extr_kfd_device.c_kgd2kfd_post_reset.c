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
struct kfd_dev {int /*<<< orphan*/  sram_ecc_flag; int /*<<< orphan*/  dqm; int /*<<< orphan*/  init_complete; } ;

/* Variables and functions */
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dqm_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfd_locked ; 
 int kfd_resume (struct kfd_dev*) ; 

int kgd2kfd_post_reset(struct kfd_dev *kfd)
{
	int ret, count;

	if (!kfd->init_complete)
		return 0;

	dqm_unlock(kfd->dqm);

	ret = kfd_resume(kfd);
	if (ret)
		return ret;
	count = atomic_dec_return(&kfd_locked);

	atomic_set(&kfd->sram_ecc_flag, 0);

	return 0;
}