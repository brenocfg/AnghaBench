#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hermes {TYPE_1__* ops; } ;
struct orinoco_private {struct hermes hw; } ;
struct TYPE_2__ {int (* read_ltv ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HERMES_RID_CURRENTBSSID ; 
 int /*<<< orphan*/  USER_BAP ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int orinoco_hw_get_current_bssid(struct orinoco_private *priv,
				 u8 *addr)
{
	struct hermes *hw = &priv->hw;
	int err;

	err = hw->ops->read_ltv(hw, USER_BAP, HERMES_RID_CURRENTBSSID,
				ETH_ALEN, NULL, addr);

	return err;
}