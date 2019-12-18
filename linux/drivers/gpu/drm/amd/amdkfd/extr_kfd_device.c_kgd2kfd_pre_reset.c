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
struct kfd_dev {int /*<<< orphan*/  dqm; int /*<<< orphan*/  init_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  dqm_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfd_signal_reset_event (struct kfd_dev*) ; 
 int /*<<< orphan*/  kgd2kfd_suspend (struct kfd_dev*) ; 

int kgd2kfd_pre_reset(struct kfd_dev *kfd)
{
	if (!kfd->init_complete)
		return 0;
	kgd2kfd_suspend(kfd);

	/* hold dqm->lock to prevent further execution*/
	dqm_lock(kfd->dqm);

	kfd_signal_reset_event(kfd);
	return 0;
}