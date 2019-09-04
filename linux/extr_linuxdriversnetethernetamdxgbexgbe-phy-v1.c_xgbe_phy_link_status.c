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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 unsigned int MDIO_STAT1_LSTATUS ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_phy_link_status(struct xgbe_prv_data *pdata, int *an_restart)
{
	unsigned int reg;

	*an_restart = 0;

	/* Link status is latched low, so read once to clear
	 * and then read again to get current state
	 */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);

	return (reg & MDIO_STAT1_LSTATUS) ? 1 : 0;
}