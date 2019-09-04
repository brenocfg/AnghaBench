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
typedef  int u32 ;
struct trinity_ps {int /*<<< orphan*/  DpmXNbPsHi; int /*<<< orphan*/  DpmXNbPsLo; int /*<<< orphan*/  Dpm0PgNbPsHi; int /*<<< orphan*/  Dpm0PgNbPsLo; } ;
struct TYPE_2__ {scalar_t__ nb_dpm_enable; } ;
struct trinity_power_info {TYPE_1__ sys_info; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int Dpm0PgNbPsHi (int /*<<< orphan*/ ) ; 
 int Dpm0PgNbPsHi_MASK ; 
 int Dpm0PgNbPsLo (int /*<<< orphan*/ ) ; 
 int Dpm0PgNbPsLo_MASK ; 
 int DpmXNbPsHi (int /*<<< orphan*/ ) ; 
 int DpmXNbPsHi_MASK ; 
 int DpmXNbPsLo (int /*<<< orphan*/ ) ; 
 int DpmXNbPsLo_MASK ; 
 int /*<<< orphan*/  NB_PSTATE_CONFIG ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 struct trinity_ps* trinity_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void trinity_setup_nbp_sim(struct radeon_device *rdev,
				  struct radeon_ps *rps)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	struct trinity_ps *new_ps = trinity_get_ps(rps);
	u32 nbpsconfig;

	if (pi->sys_info.nb_dpm_enable) {
		nbpsconfig = RREG32_SMC(NB_PSTATE_CONFIG);
		nbpsconfig &= ~(Dpm0PgNbPsLo_MASK | Dpm0PgNbPsHi_MASK | DpmXNbPsLo_MASK | DpmXNbPsHi_MASK);
		nbpsconfig |= (Dpm0PgNbPsLo(new_ps->Dpm0PgNbPsLo) |
			       Dpm0PgNbPsHi(new_ps->Dpm0PgNbPsHi) |
			       DpmXNbPsLo(new_ps->DpmXNbPsLo) |
			       DpmXNbPsHi(new_ps->DpmXNbPsHi));
		WREG32_SMC(NB_PSTATE_CONFIG, nbpsconfig);
	}
}