#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * hpd_eop_obj; } ;
struct radeon_device {TYPE_1__ mec; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cik_mec_fini(struct radeon_device *rdev)
{
	int r;

	if (rdev->mec.hpd_eop_obj) {
		r = radeon_bo_reserve(rdev->mec.hpd_eop_obj, false);
		if (unlikely(r != 0))
			dev_warn(rdev->dev, "(%d) reserve HPD EOP bo failed\n", r);
		radeon_bo_unpin(rdev->mec.hpd_eop_obj);
		radeon_bo_unreserve(rdev->mec.hpd_eop_obj);

		radeon_bo_unref(&rdev->mec.hpd_eop_obj);
		rdev->mec.hpd_eop_obj = NULL;
	}
}