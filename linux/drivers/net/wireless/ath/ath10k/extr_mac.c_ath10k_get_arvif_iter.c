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
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ath10k_vif_iter {scalar_t__ vdev_id; struct ath10k_vif* arvif; } ;
struct ath10k_vif {scalar_t__ vdev_id; } ;

/* Variables and functions */

__attribute__((used)) static void ath10k_get_arvif_iter(void *data, u8 *mac,
				  struct ieee80211_vif *vif)
{
	struct ath10k_vif_iter *arvif_iter = data;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;

	if (arvif->vdev_id == arvif_iter->vdev_id)
		arvif_iter->arvif = arvif;
}