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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int num_mec; int num_pipe; int num_queue; int /*<<< orphan*/ * hpd_eop_obj; int /*<<< orphan*/  hpd_eop_gpu_addr; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ mec; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_KAVERI ; 
 int MEC_HPD_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  cik_mec_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int radeon_bo_create (struct radeon_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int radeon_bo_kmap (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  radeon_bo_kunmap (int /*<<< orphan*/ *) ; 
 int radeon_bo_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cik_mec_init(struct radeon_device *rdev)
{
	int r;
	u32 *hpd;

	/*
	 * KV:    2 MEC, 4 Pipes/MEC, 8 Queues/Pipe - 64 Queues total
	 * CI/KB: 1 MEC, 4 Pipes/MEC, 8 Queues/Pipe - 32 Queues total
	 */
	if (rdev->family == CHIP_KAVERI)
		rdev->mec.num_mec = 2;
	else
		rdev->mec.num_mec = 1;
	rdev->mec.num_pipe = 4;
	rdev->mec.num_queue = rdev->mec.num_mec * rdev->mec.num_pipe * 8;

	if (rdev->mec.hpd_eop_obj == NULL) {
		r = radeon_bo_create(rdev,
				     rdev->mec.num_mec *rdev->mec.num_pipe * MEC_HPD_SIZE * 2,
				     PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT, 0, NULL, NULL,
				     &rdev->mec.hpd_eop_obj);
		if (r) {
			dev_warn(rdev->dev, "(%d) create HDP EOP bo failed\n", r);
			return r;
		}
	}

	r = radeon_bo_reserve(rdev->mec.hpd_eop_obj, false);
	if (unlikely(r != 0)) {
		cik_mec_fini(rdev);
		return r;
	}
	r = radeon_bo_pin(rdev->mec.hpd_eop_obj, RADEON_GEM_DOMAIN_GTT,
			  &rdev->mec.hpd_eop_gpu_addr);
	if (r) {
		dev_warn(rdev->dev, "(%d) pin HDP EOP bo failed\n", r);
		cik_mec_fini(rdev);
		return r;
	}
	r = radeon_bo_kmap(rdev->mec.hpd_eop_obj, (void **)&hpd);
	if (r) {
		dev_warn(rdev->dev, "(%d) map HDP EOP bo failed\n", r);
		cik_mec_fini(rdev);
		return r;
	}

	/* clear memory.  Not sure if this is required or not */
	memset(hpd, 0, rdev->mec.num_mec *rdev->mec.num_pipe * MEC_HPD_SIZE * 2);

	radeon_bo_kunmap(rdev->mec.hpd_eop_obj);
	radeon_bo_unreserve(rdev->mec.hpd_eop_obj);

	return 0;
}