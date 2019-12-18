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
struct intel_uncore {int dummy; } ;
struct intel_gt {struct intel_uncore* uncore; } ;
typedef  int /*<<< orphan*/  intel_engine_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  ILK_GDSR ; 
 int ILK_GRDOM_MEDIA ; 
 int ILK_GRDOM_RENDER ; 
 int ILK_GRDOM_RESET_ENABLE ; 
 int __intel_wait_for_register_fw (struct intel_uncore*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_posting_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ironlake_do_reset(struct intel_gt *gt,
			     intel_engine_mask_t engine_mask,
			     unsigned int retry)
{
	struct intel_uncore *uncore = gt->uncore;
	int ret;

	intel_uncore_write_fw(uncore, ILK_GDSR,
			      ILK_GRDOM_RENDER | ILK_GRDOM_RESET_ENABLE);
	ret = __intel_wait_for_register_fw(uncore, ILK_GDSR,
					   ILK_GRDOM_RESET_ENABLE, 0,
					   5000, 0,
					   NULL);
	if (ret) {
		DRM_DEBUG_DRIVER("Wait for render reset failed\n");
		goto out;
	}

	intel_uncore_write_fw(uncore, ILK_GDSR,
			      ILK_GRDOM_MEDIA | ILK_GRDOM_RESET_ENABLE);
	ret = __intel_wait_for_register_fw(uncore, ILK_GDSR,
					   ILK_GRDOM_RESET_ENABLE, 0,
					   5000, 0,
					   NULL);
	if (ret) {
		DRM_DEBUG_DRIVER("Wait for media reset failed\n");
		goto out;
	}

out:
	intel_uncore_write_fw(uncore, ILK_GDSR, 0);
	intel_uncore_posting_read_fw(uncore, ILK_GDSR);
	return ret;
}