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
 int /*<<< orphan*/  MDIO_MMD_VEND2 ; 
 int /*<<< orphan*/  MDIO_PCS_DIG_CTRL ; 
 int /*<<< orphan*/  MDIO_VEND2_AN_CTRL ; 
 int XGBE_AN_CL37_INT_MASK ; 
 int XGBE_PCS_CL37_BP ; 
 int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_an37_disable_interrupts(struct xgbe_prv_data *pdata)
{
	int reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL);
	reg &= ~XGBE_AN_CL37_INT_MASK;
	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL, reg);

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL);
	reg &= ~XGBE_PCS_CL37_BP;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL, reg);
}