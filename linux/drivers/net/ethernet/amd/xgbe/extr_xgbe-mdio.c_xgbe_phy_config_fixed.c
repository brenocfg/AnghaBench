#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_4__ {int (* get_mode ) (struct xgbe_prv_data*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {TYPE_3__ phy; TYPE_2__ phy_if; int /*<<< orphan*/  netdev; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
#define  XGBE_MODE_KR 135 
#define  XGBE_MODE_KX_1000 134 
#define  XGBE_MODE_KX_2500 133 
#define  XGBE_MODE_SFI 132 
#define  XGBE_MODE_SGMII_100 131 
#define  XGBE_MODE_SGMII_1000 130 
#define  XGBE_MODE_UNKNOWN 129 
#define  XGBE_MODE_X 128 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_an_disable (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_set_mode (struct xgbe_prv_data*,int) ; 

__attribute__((used)) static int xgbe_phy_config_fixed(struct xgbe_prv_data *pdata)
{
	enum xgbe_mode mode;

	netif_dbg(pdata, link, pdata->netdev, "fixed PHY configuration\n");

	/* Disable auto-negotiation */
	xgbe_an_disable(pdata);

	/* Set specified mode for specified speed */
	mode = pdata->phy_if.phy_impl.get_mode(pdata, pdata->phy.speed);
	switch (mode) {
	case XGBE_MODE_KX_1000:
	case XGBE_MODE_KX_2500:
	case XGBE_MODE_KR:
	case XGBE_MODE_SGMII_100:
	case XGBE_MODE_SGMII_1000:
	case XGBE_MODE_X:
	case XGBE_MODE_SFI:
		break;
	case XGBE_MODE_UNKNOWN:
	default:
		return -EINVAL;
	}

	/* Validate duplex mode */
	if (pdata->phy.duplex != DUPLEX_FULL)
		return -EINVAL;

	xgbe_set_mode(pdata, mode);

	return 0;
}