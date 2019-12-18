#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_hw {struct brcms_info* priv; } ;
struct brcms_info {TYPE_2__* pub; scalar_t__ wlc; } ;
struct bcma_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ieee_hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 struct ieee80211_hw* bcma_get_drvdata (struct bcma_device*) ; 
 int /*<<< orphan*/  bcma_set_drvdata (struct bcma_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_free (struct brcms_info*) ; 
 int /*<<< orphan*/  brcms_led_unregister (struct brcms_info*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiphy_rfkill_stop_polling (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_remove(struct bcma_device *pdev)
{
	struct ieee80211_hw *hw = bcma_get_drvdata(pdev);
	struct brcms_info *wl = hw->priv;

	if (wl->wlc) {
		brcms_led_unregister(wl);
		wiphy_rfkill_set_hw_state(wl->pub->ieee_hw->wiphy, false);
		wiphy_rfkill_stop_polling(wl->pub->ieee_hw->wiphy);
		ieee80211_unregister_hw(hw);
	}

	brcms_free(wl);

	bcma_set_drvdata(pdev, NULL);
	ieee80211_free_hw(hw);
}