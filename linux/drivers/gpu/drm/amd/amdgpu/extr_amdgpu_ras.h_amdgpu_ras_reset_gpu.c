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
struct amdgpu_ras {int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  in_recovery; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int amdgpu_ras_reset_gpu(struct amdgpu_device *adev,
		bool is_baco)
{
	struct amdgpu_ras *ras = amdgpu_ras_get_context(adev);

	if (atomic_cmpxchg(&ras->in_recovery, 0, 1) == 0)
		schedule_work(&ras->recovery_work);
	return 0;
}