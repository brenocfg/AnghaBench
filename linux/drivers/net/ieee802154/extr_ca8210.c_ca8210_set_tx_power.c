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
struct ieee802154_hw {struct ca8210_priv* priv; } ;
struct ca8210_priv {int /*<<< orphan*/  spi; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_TRANSMIT_POWER ; 
 int link_to_linux_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlme_set_request_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca8210_set_tx_power(struct ieee802154_hw *hw, s32 mbm)
{
	struct ca8210_priv *priv = hw->priv;

	mbm /= 100;
	return link_to_linux_err(
		mlme_set_request_sync(PHY_TRANSMIT_POWER, 0, 1, &mbm, priv->spi)
	);
}