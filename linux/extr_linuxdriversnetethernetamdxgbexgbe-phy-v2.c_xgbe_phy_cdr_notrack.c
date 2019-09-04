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
struct xgbe_prv_data {int /*<<< orphan*/  debugfs_an_cdr_workaround; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int phy_cdr_notrack; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_VEND2_PMA_CDR_CONTROL ; 
 int /*<<< orphan*/  XGBE_PMA_CDR_TRACK_EN_MASK ; 
 int /*<<< orphan*/  XGBE_PMA_CDR_TRACK_EN_OFF ; 
 int /*<<< orphan*/  XMDIO_WRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_phy_rrc (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_cdr_notrack(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	if (!pdata->debugfs_an_cdr_workaround)
		return;

	if (phy_data->phy_cdr_notrack)
		return;

	XMDIO_WRITE_BITS(pdata, MDIO_MMD_PMAPMD, MDIO_VEND2_PMA_CDR_CONTROL,
			 XGBE_PMA_CDR_TRACK_EN_MASK,
			 XGBE_PMA_CDR_TRACK_EN_OFF);

	xgbe_phy_rrc(pdata);

	phy_data->phy_cdr_notrack = 1;
}