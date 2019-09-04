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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct xgbe_prv_data {int dummy; } ;
typedef  int /*<<< orphan*/  mii_data ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_SFP_PHY_ADDRESS ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int xgbe_phy_i2c_write (struct xgbe_prv_data*,int /*<<< orphan*/ ,int*,int) ; 
 int xgbe_phy_sfp_get_mux (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_put_mux (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_i2c_mii_write(struct xgbe_prv_data *pdata, int reg, u16 val)
{
	__be16 *mii_val;
	u8 mii_data[3];
	int ret;

	ret = xgbe_phy_sfp_get_mux(pdata);
	if (ret)
		return ret;

	mii_data[0] = reg & 0xff;
	mii_val = (__be16 *)&mii_data[1];
	*mii_val = cpu_to_be16(val);

	ret = xgbe_phy_i2c_write(pdata, XGBE_SFP_PHY_ADDRESS,
				 mii_data, sizeof(mii_data));

	xgbe_phy_sfp_put_mux(pdata);

	return ret;
}