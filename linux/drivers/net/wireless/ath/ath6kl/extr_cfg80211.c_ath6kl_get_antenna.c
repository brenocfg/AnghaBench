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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_ant; int /*<<< orphan*/  tx_ant; } ;
struct ath6kl {TYPE_1__ hw; } ;

/* Variables and functions */
 struct ath6kl* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ath6kl_get_antenna(struct wiphy *wiphy,
			      u32 *tx_ant, u32 *rx_ant)
{
	struct ath6kl *ar = wiphy_priv(wiphy);
	*tx_ant = ar->hw.tx_ant;
	*rx_ant = ar->hw.rx_ant;
	return 0;
}