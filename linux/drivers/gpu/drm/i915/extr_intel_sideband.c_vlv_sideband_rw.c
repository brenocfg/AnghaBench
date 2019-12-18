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
typedef  int u32 ;
struct intel_uncore {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  sb_lock; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int IOSF_BAR_SHIFT ; 
 int IOSF_BYTE_ENABLES_SHIFT ; 
 int IOSF_DEVFN_SHIFT ; 
 int IOSF_OPCODE_SHIFT ; 
 int IOSF_PORT_PUNIT ; 
 int IOSF_PORT_SHIFT ; 
 int IOSF_SB_BUSY ; 
 int SB_CRRDDA_NP ; 
 int SB_MRD_NP ; 
 int /*<<< orphan*/  VLV_IOSF_ADDR ; 
 int /*<<< orphan*/  VLV_IOSF_DATA ; 
 int /*<<< orphan*/  VLV_IOSF_DOORBELL_REQ ; 
 scalar_t__ __intel_wait_for_register_fw (struct intel_uncore*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int intel_uncore_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ intel_wait_for_register (struct intel_uncore*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iosf_mbi_assert_punit_acquired () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int vlv_sideband_rw(struct drm_i915_private *i915,
			   u32 devfn, u32 port, u32 opcode,
			   u32 addr, u32 *val)
{
	struct intel_uncore *uncore = &i915->uncore;
	const bool is_read = (opcode == SB_MRD_NP || opcode == SB_CRRDDA_NP);
	int err;

	lockdep_assert_held(&i915->sb_lock);
	if (port == IOSF_PORT_PUNIT)
		iosf_mbi_assert_punit_acquired();

	/* Flush the previous comms, just in case it failed last time. */
	if (intel_wait_for_register(uncore,
				    VLV_IOSF_DOORBELL_REQ, IOSF_SB_BUSY, 0,
				    5)) {
		DRM_DEBUG_DRIVER("IOSF sideband idle wait (%s) timed out\n",
				 is_read ? "read" : "write");
		return -EAGAIN;
	}

	preempt_disable();

	intel_uncore_write_fw(uncore, VLV_IOSF_ADDR, addr);
	intel_uncore_write_fw(uncore, VLV_IOSF_DATA, is_read ? 0 : *val);
	intel_uncore_write_fw(uncore, VLV_IOSF_DOORBELL_REQ,
			      (devfn << IOSF_DEVFN_SHIFT) |
			      (opcode << IOSF_OPCODE_SHIFT) |
			      (port << IOSF_PORT_SHIFT) |
			      (0xf << IOSF_BYTE_ENABLES_SHIFT) |
			      (0 << IOSF_BAR_SHIFT) |
			      IOSF_SB_BUSY);

	if (__intel_wait_for_register_fw(uncore,
					 VLV_IOSF_DOORBELL_REQ, IOSF_SB_BUSY, 0,
					 10000, 0, NULL) == 0) {
		if (is_read)
			*val = intel_uncore_read_fw(uncore, VLV_IOSF_DATA);
		err = 0;
	} else {
		DRM_DEBUG_DRIVER("IOSF sideband finish wait (%s) timed out\n",
				 is_read ? "read" : "write");
		err = -ETIMEDOUT;
	}

	preempt_enable();

	return err;
}