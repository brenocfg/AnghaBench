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
typedef  int /*<<< orphan*/  u32 ;
struct intel_uncore {int dummy; } ;
struct intel_gt {struct intel_uncore* uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN6_GDRST ; 
 int __intel_wait_for_register_fw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen6_hw_domain_reset(struct intel_gt *gt, u32 hw_domain_mask)
{
	struct intel_uncore *uncore = gt->uncore;
	int err;

	/*
	 * GEN6_GDRST is not in the gt power well, no need to check
	 * for fifo space for the write or forcewake the chip for
	 * the read
	 */
	intel_uncore_write_fw(uncore, GEN6_GDRST, hw_domain_mask);

	/* Wait for the device to ack the reset requests */
	err = __intel_wait_for_register_fw(uncore,
					   GEN6_GDRST, hw_domain_mask, 0,
					   500, 0,
					   NULL);
	if (err)
		DRM_DEBUG_DRIVER("Wait for 0x%08x engines reset failed\n",
				 hw_domain_mask);

	return err;
}