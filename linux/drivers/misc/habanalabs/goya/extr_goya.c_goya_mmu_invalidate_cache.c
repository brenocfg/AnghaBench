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
struct hl_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mmu_cache_lock; scalar_t__ pldm; struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOYA_PLDM_MMU_TIMEOUT_USEC ; 
 int HW_CAP_MMU ; 
 int /*<<< orphan*/  MMU_CONFIG_TIMEOUT_USEC ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_notice_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int hl_poll_timeout (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSTLB_INV_ALL_START ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void goya_mmu_invalidate_cache(struct hl_device *hdev, bool is_hard)
{
	struct goya_device *goya = hdev->asic_specific;
	u32 status, timeout_usec;
	int rc;

	if (!(goya->hw_cap_initialized & HW_CAP_MMU))
		return;

	/* no need in L1 only invalidation in Goya */
	if (!is_hard)
		return;

	if (hdev->pldm)
		timeout_usec = GOYA_PLDM_MMU_TIMEOUT_USEC;
	else
		timeout_usec = MMU_CONFIG_TIMEOUT_USEC;

	mutex_lock(&hdev->mmu_cache_lock);

	/* L0 & L1 invalidation */
	WREG32(mmSTLB_INV_ALL_START, 1);

	rc = hl_poll_timeout(
		hdev,
		mmSTLB_INV_ALL_START,
		status,
		!status,
		1000,
		timeout_usec);

	mutex_unlock(&hdev->mmu_cache_lock);

	if (rc)
		dev_notice_ratelimited(hdev->dev,
			"Timeout when waiting for MMU cache invalidation\n");
}