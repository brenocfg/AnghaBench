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
typedef  enum xgbe_mdio_mode { ____Placeholder_xgbe_mdio_mode } xgbe_mdio_mode ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAC_MDIOCL22R ; 
#define  XGBE_MDIO_MODE_CL22 129 
#define  XGBE_MDIO_MODE_CL45 128 
 unsigned int XGMAC_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int XGMAC_MAX_C22_PORT ; 

__attribute__((used)) static int xgbe_set_ext_mii_mode(struct xgbe_prv_data *pdata, unsigned int port,
				 enum xgbe_mdio_mode mode)
{
	unsigned int reg_val = XGMAC_IOREAD(pdata, MAC_MDIOCL22R);

	switch (mode) {
	case XGBE_MDIO_MODE_CL22:
		if (port > XGMAC_MAX_C22_PORT)
			return -EINVAL;
		reg_val |= (1 << port);
		break;
	case XGBE_MDIO_MODE_CL45:
		break;
	default:
		return -EINVAL;
	}

	XGMAC_IOWRITE(pdata, MAC_MDIOCL22R, reg_val);

	return 0;
}