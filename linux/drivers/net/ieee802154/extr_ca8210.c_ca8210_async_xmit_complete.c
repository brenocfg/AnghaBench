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
typedef  scalar_t__ u8 ;
struct ieee802154_hw {struct ca8210_priv* priv; } ;
struct ca8210_priv {scalar_t__ nextmsduhandle; int async_tx_pending; int /*<<< orphan*/  tx_skb; int /*<<< orphan*/  hw; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ MAC_TRANSACTION_OVERFLOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ieee802154_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_xmit_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ca8210_async_xmit_complete(
	struct ieee802154_hw  *hw,
	u8                     msduhandle,
	u8                     status)
{
	struct ca8210_priv *priv = hw->priv;

	if (priv->nextmsduhandle != msduhandle) {
		dev_err(
			&priv->spi->dev,
			"Unexpected msdu_handle on data confirm, Expected %d, got %d\n",
			priv->nextmsduhandle,
			msduhandle
		);
		return -EIO;
	}

	priv->async_tx_pending = false;
	priv->nextmsduhandle++;

	if (status) {
		dev_err(
			&priv->spi->dev,
			"Link transmission unsuccessful, status = %d\n",
			status
		);
		if (status != MAC_TRANSACTION_OVERFLOW) {
			ieee802154_wake_queue(priv->hw);
			return 0;
		}
	}
	ieee802154_xmit_complete(priv->hw, priv->tx_skb, true);

	return 0;
}