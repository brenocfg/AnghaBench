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
struct ieee80211_sta {int /*<<< orphan*/  tdls; } ;
struct ath10k_vif {scalar_t__ vdev_type; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  num_stations; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 scalar_t__ WMI_VDEV_TYPE_STA ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_mac_dec_num_stations(struct ath10k_vif *arvif,
					struct ieee80211_sta *sta)
{
	struct ath10k *ar = arvif->ar;

	lockdep_assert_held(&ar->conf_mutex);

	if (arvif->vdev_type == WMI_VDEV_TYPE_STA && !sta->tdls)
		return;

	ar->num_stations--;
}