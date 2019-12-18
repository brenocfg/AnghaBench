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
struct ca8210_priv {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CURRENT_CHANNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int link_to_linux_err (scalar_t__) ; 
 scalar_t__ mlme_set_request_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,TYPE_1__*) ; 

__attribute__((used)) static int ca8210_set_channel(
	struct ieee802154_hw  *hw,
	u8                     page,
	u8                     channel
)
{
	u8 status;
	struct ca8210_priv *priv = hw->priv;

	status = mlme_set_request_sync(
		PHY_CURRENT_CHANNEL,
		0,
		1,
		&channel,
		priv->spi
	);
	if (status) {
		dev_err(
			&priv->spi->dev,
			"error setting channel, MLME-SET.confirm status = %d\n",
			status
		);
	}
	return link_to_linux_err(status);
}