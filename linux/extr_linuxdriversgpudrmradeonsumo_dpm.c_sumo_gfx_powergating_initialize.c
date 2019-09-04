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
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_CG_VOLTAGE_CNTL ; 
 int /*<<< orphan*/  CG_PWR_GATING_CNTL ; 
 int /*<<< orphan*/  CG_SCRATCH2 ; 
 scalar_t__ CHIP_PALM ; 
 int DPPD (int) ; 
 int DPPD_MASK ; 
 int DPPU (int) ; 
 int DPPU_MASK ; 
 int IT (int) ; 
 int IT_MASK ; 
 int MPPD (int) ; 
 int MPPD_MASK ; 
 int MPPU (int) ; 
 int MPPU_MASK ; 
 int PCP (int) ; 
 int PCP_MASK ; 
 int PCV (int) ; 
 int PCV_MASK ; 
 int PGP (int) ; 
 int PGP_MASK ; 
 int PGS (int) ; 
 int PGS_MASK ; 
 int PGU (int) ; 
 int PGU_MASK ; 
 int PWR_GATING_EN ; 
 int /*<<< orphan*/  RCU_PWR_GATING_CNTL ; 
 int /*<<< orphan*/  RCU_PWR_GATING_CNTL_2 ; 
 int /*<<< orphan*/  RCU_PWR_GATING_CNTL_3 ; 
 int /*<<< orphan*/  RCU_PWR_GATING_CNTL_4 ; 
 int /*<<< orphan*/  RCU_PWR_GATING_CNTL_5 ; 
 int /*<<< orphan*/  RCU_PWR_GATING_SEQ0 ; 
 int /*<<< orphan*/  RCU_PWR_GATING_SEQ1 ; 
 int RREG32_RCU (int /*<<< orphan*/ ) ; 
 int RSVD_MASK ; 
 int RT (int) ; 
 int RT_MASK ; 
 int /*<<< orphan*/  SUMO_GFXPOWERGATINGT_DFLT ; 
 int /*<<< orphan*/  SUMO_VOLTAGEDROPT_DFLT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WREG32_RCU (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int /*<<< orphan*/ ,int,int,int*,int*) ; 
 int radeon_get_xclk (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_smu_pg_init (struct radeon_device*) ; 

__attribute__((used)) static void sumo_gfx_powergating_initialize(struct radeon_device *rdev)
{
	u32 rcu_pwr_gating_cntl;
	u32 p, u;
	u32 p_c, p_p, d_p;
	u32 r_t, i_t;
	u32 xclk = radeon_get_xclk(rdev);

	if (rdev->family == CHIP_PALM) {
		p_c = 4;
		d_p = 10;
		r_t = 10;
		i_t = 4;
		p_p = 50 + 1000/200 + 6 * 32;
	} else {
		p_c = 16;
		d_p = 50;
		r_t = 50;
		i_t  = 50;
		p_p = 113;
	}

	WREG32(CG_SCRATCH2, 0x01B60A17);

	r600_calculate_u_and_p(SUMO_GFXPOWERGATINGT_DFLT,
			       xclk, 16, &p, &u);

	WREG32_P(CG_PWR_GATING_CNTL, PGP(p) | PGU(u),
		 ~(PGP_MASK | PGU_MASK));

	r600_calculate_u_and_p(SUMO_VOLTAGEDROPT_DFLT,
			       xclk, 16, &p, &u);

	WREG32_P(CG_CG_VOLTAGE_CNTL, PGP(p) | PGU(u),
		 ~(PGP_MASK | PGU_MASK));

	if (rdev->family == CHIP_PALM) {
		WREG32_RCU(RCU_PWR_GATING_SEQ0, 0x10103210);
		WREG32_RCU(RCU_PWR_GATING_SEQ1, 0x10101010);
	} else {
		WREG32_RCU(RCU_PWR_GATING_SEQ0, 0x76543210);
		WREG32_RCU(RCU_PWR_GATING_SEQ1, 0xFEDCBA98);
	}

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL);
	rcu_pwr_gating_cntl &=
		~(RSVD_MASK | PCV_MASK | PGS_MASK);
	rcu_pwr_gating_cntl |= PCV(p_c) | PGS(1) | PWR_GATING_EN;
	if (rdev->family == CHIP_PALM) {
		rcu_pwr_gating_cntl &= ~PCP_MASK;
		rcu_pwr_gating_cntl |= PCP(0x77);
	}
	WREG32_RCU(RCU_PWR_GATING_CNTL, rcu_pwr_gating_cntl);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_2);
	rcu_pwr_gating_cntl &= ~(MPPU_MASK | MPPD_MASK);
	rcu_pwr_gating_cntl |= MPPU(p_p) | MPPD(50);
	WREG32_RCU(RCU_PWR_GATING_CNTL_2, rcu_pwr_gating_cntl);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_3);
	rcu_pwr_gating_cntl &= ~(DPPU_MASK | DPPD_MASK);
	rcu_pwr_gating_cntl |= DPPU(d_p) | DPPD(50);
	WREG32_RCU(RCU_PWR_GATING_CNTL_3, rcu_pwr_gating_cntl);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_4);
	rcu_pwr_gating_cntl &= ~(RT_MASK | IT_MASK);
	rcu_pwr_gating_cntl |= RT(r_t) | IT(i_t);
	WREG32_RCU(RCU_PWR_GATING_CNTL_4, rcu_pwr_gating_cntl);

	if (rdev->family == CHIP_PALM)
		WREG32_RCU(RCU_PWR_GATING_CNTL_5, 0xA02);

	sumo_smu_pg_init(rdev);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL);
	rcu_pwr_gating_cntl &=
		~(RSVD_MASK | PCV_MASK | PGS_MASK);
	rcu_pwr_gating_cntl |= PCV(p_c) | PGS(4) | PWR_GATING_EN;
	if (rdev->family == CHIP_PALM) {
		rcu_pwr_gating_cntl &= ~PCP_MASK;
		rcu_pwr_gating_cntl |= PCP(0x77);
	}
	WREG32_RCU(RCU_PWR_GATING_CNTL, rcu_pwr_gating_cntl);

	if (rdev->family == CHIP_PALM) {
		rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_2);
		rcu_pwr_gating_cntl &= ~(MPPU_MASK | MPPD_MASK);
		rcu_pwr_gating_cntl |= MPPU(113) | MPPD(50);
		WREG32_RCU(RCU_PWR_GATING_CNTL_2, rcu_pwr_gating_cntl);

		rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_3);
		rcu_pwr_gating_cntl &= ~(DPPU_MASK | DPPD_MASK);
		rcu_pwr_gating_cntl |= DPPU(16) | DPPD(50);
		WREG32_RCU(RCU_PWR_GATING_CNTL_3, rcu_pwr_gating_cntl);
	}

	sumo_smu_pg_init(rdev);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL);
	rcu_pwr_gating_cntl &=
		~(RSVD_MASK | PCV_MASK | PGS_MASK);
	rcu_pwr_gating_cntl |= PGS(5) | PWR_GATING_EN;

	if (rdev->family == CHIP_PALM) {
		rcu_pwr_gating_cntl |= PCV(4);
		rcu_pwr_gating_cntl &= ~PCP_MASK;
		rcu_pwr_gating_cntl |= PCP(0x77);
	} else
		rcu_pwr_gating_cntl |= PCV(11);
	WREG32_RCU(RCU_PWR_GATING_CNTL, rcu_pwr_gating_cntl);

	if (rdev->family == CHIP_PALM) {
		rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_2);
		rcu_pwr_gating_cntl &= ~(MPPU_MASK | MPPD_MASK);
		rcu_pwr_gating_cntl |= MPPU(113) | MPPD(50);
		WREG32_RCU(RCU_PWR_GATING_CNTL_2, rcu_pwr_gating_cntl);

		rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_3);
		rcu_pwr_gating_cntl &= ~(DPPU_MASK | DPPD_MASK);
		rcu_pwr_gating_cntl |= DPPU(22) | DPPD(50);
		WREG32_RCU(RCU_PWR_GATING_CNTL_3, rcu_pwr_gating_cntl);
	}

	sumo_smu_pg_init(rdev);
}