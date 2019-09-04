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
typedef  enum xgbe_rx { ____Placeholder_xgbe_rx } xgbe_rx ;
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_LPX ; 
 int /*<<< orphan*/  MDIO_AN_XNP ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 unsigned int XGBE_XNP_NP_EXCHANGE ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xgbe_an73_tx_training (struct xgbe_prv_data*,int*) ; 
 int xgbe_an73_tx_xnp (struct xgbe_prv_data*,int*) ; 

__attribute__((used)) static enum xgbe_an xgbe_an73_rx_xnp(struct xgbe_prv_data *pdata,
				     enum xgbe_rx *state)
{
	unsigned int ad_reg, lp_reg;

	/* Check Extended Next Page support */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_XNP);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPX);

	return ((ad_reg & XGBE_XNP_NP_EXCHANGE) ||
		(lp_reg & XGBE_XNP_NP_EXCHANGE))
	       ? xgbe_an73_tx_xnp(pdata, state)
	       : xgbe_an73_tx_training(pdata, state);
}