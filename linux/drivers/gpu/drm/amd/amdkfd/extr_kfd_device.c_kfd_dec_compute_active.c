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
struct kfd_dev {int /*<<< orphan*/  kgd; int /*<<< orphan*/  compute_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_set_compute_idle (int /*<<< orphan*/ ,int) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 

void kfd_dec_compute_active(struct kfd_dev *kfd)
{
	int count = atomic_dec_return(&kfd->compute_profile);

	if (count == 0)
		amdgpu_amdkfd_set_compute_idle(kfd->kgd, true);
	WARN_ONCE(count < 0, "Compute profile ref. count error");
}