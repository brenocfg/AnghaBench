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
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QMAN_FENCE_TIMEOUT_USEC ; 
 int /*<<< orphan*/  QMAN_STOP_TIMEOUT_USEC ; 
 int RREG32 (int) ; 
 int TPC0_QM_CP_STS_FENCE_IN_PROGRESS_MASK ; 
 int TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT ; 
 int TPC0_QM_GLBL_STS0_CP_IS_STOP_MASK ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hl_poll_timeout (struct hl_device*,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_stop_queue(struct hl_device *hdev, u32 cfg_reg,
				u32 cp_sts_reg, u32 glbl_sts0_reg)
{
	int rc;
	u32 status;

	/* use the values of TPC0 as they are all the same*/

	WREG32(cfg_reg, 1 << TPC0_QM_GLBL_CFG1_CP_STOP_SHIFT);

	status = RREG32(cp_sts_reg);
	if (status & TPC0_QM_CP_STS_FENCE_IN_PROGRESS_MASK) {
		rc = hl_poll_timeout(
			hdev,
			cp_sts_reg,
			status,
			!(status & TPC0_QM_CP_STS_FENCE_IN_PROGRESS_MASK),
			1000,
			QMAN_FENCE_TIMEOUT_USEC);

		/* if QMAN is stuck in fence no need to check for stop */
		if (rc)
			return 0;
	}

	rc = hl_poll_timeout(
		hdev,
		glbl_sts0_reg,
		status,
		(status & TPC0_QM_GLBL_STS0_CP_IS_STOP_MASK),
		1000,
		QMAN_STOP_TIMEOUT_USEC);

	if (rc) {
		dev_err(hdev->dev,
			"Timeout while waiting for QMAN to stop\n");
		return -EINVAL;
	}

	return 0;
}