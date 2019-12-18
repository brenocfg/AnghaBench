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
struct xgbe_prv_data {TYPE_1__* netdev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  JE ; 
 int /*<<< orphan*/  MAC_RCR ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ XGMAC_STD_PACKET_MTU ; 

__attribute__((used)) static void xgbe_config_jumbo_enable(struct xgbe_prv_data *pdata)
{
	unsigned int val;

	val = (pdata->netdev->mtu > XGMAC_STD_PACKET_MTU) ? 1 : 0;

	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, JE, val);
}