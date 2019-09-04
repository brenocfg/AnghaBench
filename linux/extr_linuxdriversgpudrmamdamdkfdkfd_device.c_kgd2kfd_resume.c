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
struct kfd_dev {int /*<<< orphan*/  init_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfd_locked ; 
 int kfd_resume (struct kfd_dev*) ; 
 int kfd_resume_all_processes () ; 

int kgd2kfd_resume(struct kfd_dev *kfd)
{
	int ret, count;

	if (!kfd->init_complete)
		return 0;

	ret = kfd_resume(kfd);
	if (ret)
		return ret;

	count = atomic_dec_return(&kfd_locked);
	WARN_ONCE(count < 0, "KFD suspend / resume ref. error");
	if (count == 0)
		ret = kfd_resume_all_processes();

	return ret;
}