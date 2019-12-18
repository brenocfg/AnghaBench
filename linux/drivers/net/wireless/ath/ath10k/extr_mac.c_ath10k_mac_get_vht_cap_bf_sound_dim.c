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
struct ath10k {int vht_cap_info; } ;

/* Variables and functions */
 int IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK ; 
 int IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT ; 

__attribute__((used)) static int ath10k_mac_get_vht_cap_bf_sound_dim(struct ath10k *ar)
{
	int sound_dim = ar->vht_cap_info;

	sound_dim &= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK;
	sound_dim >>= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT;

	/* If the sounding dimension is not advertised by the firmware,
	 * let's use a default value of 1
	 */
	if (sound_dim == 0)
		return 1;

	return sound_dim;
}