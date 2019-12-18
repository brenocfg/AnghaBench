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
typedef  int /*<<< orphan*/  u8 ;
struct ieee802154_hw {struct ca8210_priv* priv; } ;
struct ca8210_priv {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWME_EDVALUE ; 
 int /*<<< orphan*/  hwme_get_request_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int link_to_linux_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca8210_get_ed(struct ieee802154_hw *hw, u8 *level)
{
	u8 lenvar;
	struct ca8210_priv *priv = hw->priv;

	return link_to_linux_err(
		hwme_get_request_sync(HWME_EDVALUE, &lenvar, level, priv->spi)
	);
}