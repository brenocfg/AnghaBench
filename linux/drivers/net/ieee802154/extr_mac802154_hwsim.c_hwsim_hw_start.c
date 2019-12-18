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
struct ieee802154_hw {struct hwsim_phy* priv; } ;
struct hwsim_phy {int suspended; } ;

/* Variables and functions */

__attribute__((used)) static int hwsim_hw_start(struct ieee802154_hw *hw)
{
	struct hwsim_phy *phy = hw->priv;

	phy->suspended = false;
	return 0;
}