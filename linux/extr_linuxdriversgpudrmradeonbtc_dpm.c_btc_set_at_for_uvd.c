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
struct rv7xx_power_info {int rlp; int rmp; int lhp; int lmp; } ;
struct radeon_ps {int /*<<< orphan*/  class2; int /*<<< orphan*/  class; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {TYPE_1__* ats; int /*<<< orphan*/  smu_uvd_hs; } ;
struct TYPE_2__ {int rlp; int rmp; int lhp; int lmp; } ;

/* Variables and functions */
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 scalar_t__ r600_is_uvd_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void btc_set_at_for_uvd(struct radeon_device *rdev,
			       struct radeon_ps *radeon_new_state)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	int idx = 0;

	if (r600_is_uvd_state(radeon_new_state->class, radeon_new_state->class2))
		idx = 1;

	if ((idx == 1) && !eg_pi->smu_uvd_hs) {
		pi->rlp = 10;
		pi->rmp = 100;
		pi->lhp = 100;
		pi->lmp = 10;
	} else {
		pi->rlp = eg_pi->ats[idx].rlp;
		pi->rmp = eg_pi->ats[idx].rmp;
		pi->lhp = eg_pi->ats[idx].lhp;
		pi->lmp = eg_pi->ats[idx].lmp;
	}

}