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
typedef  int /*<<< orphan*/  u16 ;
struct xgbe_prv_data {int dummy; } ;
typedef  enum xgbe_rx { ____Placeholder_xgbe_rx } xgbe_rx ;
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
 scalar_t__ MDIO_AN_XNP ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int XGBE_AN_PAGE_RECEIVED ; 
 int XGBE_RX_XNP ; 
 int /*<<< orphan*/  XGBE_XNP_MCF_NULL_MESSAGE ; 
 int /*<<< orphan*/  XGBE_XNP_MP_FORMATTED ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum xgbe_an xgbe_an73_tx_xnp(struct xgbe_prv_data *pdata,
				     enum xgbe_rx *state)
{
	u16 msg;

	*state = XGBE_RX_XNP;

	msg = XGBE_XNP_MCF_NULL_MESSAGE;
	msg |= XGBE_XNP_MP_FORMATTED;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP + 2, 0);
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP + 1, 0);
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP, msg);

	return XGBE_AN_PAGE_RECEIVED;
}