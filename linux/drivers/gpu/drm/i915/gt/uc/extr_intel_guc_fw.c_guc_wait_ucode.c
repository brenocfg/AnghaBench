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

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOEXEC ; 
 int ENXIO ; 
 int GS_BOOTROM_MASK ; 
 int GS_BOOTROM_RSA_FAILED ; 
 int GS_UKERNEL_EXCEPTION ; 
 int GS_UKERNEL_MASK ; 
 int /*<<< orphan*/  SOFT_SCRATCH (int) ; 
 int /*<<< orphan*/  guc_ready (struct intel_uncore*,int*) ; 
 int /*<<< orphan*/  intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int wait_for (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int guc_wait_ucode(struct intel_uncore *uncore)
{
	u32 status;
	int ret;

	/*
	 * Wait for the GuC to start up.
	 * NB: Docs recommend not using the interrupt for completion.
	 * Measurements indicate this should take no more than 20ms, so a
	 * timeout here indicates that the GuC has failed and is unusable.
	 * (Higher levels of the driver may decide to reset the GuC and
	 * attempt the ucode load again if this happens.)
	 */
	ret = wait_for(guc_ready(uncore, &status), 100);
	DRM_DEBUG_DRIVER("GuC status %#x\n", status);

	if ((status & GS_BOOTROM_MASK) == GS_BOOTROM_RSA_FAILED) {
		DRM_ERROR("GuC firmware signature verification failed\n");
		ret = -ENOEXEC;
	}

	if ((status & GS_UKERNEL_MASK) == GS_UKERNEL_EXCEPTION) {
		DRM_ERROR("GuC firmware exception. EIP: %#x\n",
			  intel_uncore_read(uncore, SOFT_SCRATCH(13)));
		ret = -ENXIO;
	}

	return ret;
}