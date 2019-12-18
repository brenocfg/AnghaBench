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
typedef  int u8 ;
struct ieee802154_hw {struct ca8210_priv* priv; } ;
struct ca8210_priv {TYPE_1__* spi; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWME_EDTHRESHOLD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hwme_set_request_sync (int /*<<< orphan*/ ,int,int*,TYPE_1__*) ; 
 int link_to_linux_err (int) ; 

__attribute__((used)) static int ca8210_set_cca_ed_level(struct ieee802154_hw *hw, s32 level)
{
	u8 status;
	u8 ed_threshold = (level / 100) * 2 + 256;
	struct ca8210_priv *priv = hw->priv;

	status = hwme_set_request_sync(
		HWME_EDTHRESHOLD,
		1,
		&ed_threshold,
		priv->spi
	);
	if (status) {
		dev_err(
			&priv->spi->dev,
			"error setting ed threshold, HWME-SET.confirm status = %d",
			status
		);
	}
	return link_to_linux_err(status);
}