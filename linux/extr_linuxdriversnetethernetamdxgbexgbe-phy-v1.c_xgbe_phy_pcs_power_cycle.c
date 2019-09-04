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
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 unsigned int MDIO_CTRL1_LPOWER ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void xgbe_phy_pcs_power_cycle(struct xgbe_prv_data *pdata)
{
	unsigned int reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);

	reg |= MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);

	usleep_range(75, 100);

	reg &= ~MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);
}