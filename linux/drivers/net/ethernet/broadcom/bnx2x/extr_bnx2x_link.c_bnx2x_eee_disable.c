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
struct link_vars {int /*<<< orphan*/  eee_status; } ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_EEE_ADV ; 
 scalar_t__ MISC_REG_CPMU_LP_FW_ENABLE_P0 ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM_EEE_ADV_STATUS_MASK ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bnx2x_eee_disable(struct bnx2x_phy *phy,
				struct link_params *params,
				struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;

	/* Make Certain LPI is disabled */
	REG_WR(bp, MISC_REG_CPMU_LP_FW_ENABLE_P0 + (params->port << 2), 0);

	bnx2x_cl45_write(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_EEE_ADV, 0x0);

	vars->eee_status &= ~SHMEM_EEE_ADV_STATUS_MASK;

	return 0;
}