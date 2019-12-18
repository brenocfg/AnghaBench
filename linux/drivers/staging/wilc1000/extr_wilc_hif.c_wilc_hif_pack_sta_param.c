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
struct station_parameters {scalar_t__ supported_rates_len; int /*<<< orphan*/  sta_flags_set; int /*<<< orphan*/  sta_flags_mask; scalar_t__ ht_capa; scalar_t__* supported_rates; int /*<<< orphan*/  aid; } ;
struct ieee80211_ht_cap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wilc_hif_pack_sta_param(u8 *cur_byte, const u8 *mac,
				    struct station_parameters *params)
{
	ether_addr_copy(cur_byte, mac);
	cur_byte += ETH_ALEN;

	put_unaligned_le16(params->aid, cur_byte);
	cur_byte += 2;

	*cur_byte++ = params->supported_rates_len;
	if (params->supported_rates_len > 0)
		memcpy(cur_byte, params->supported_rates,
		       params->supported_rates_len);
	cur_byte += params->supported_rates_len;

	if (params->ht_capa) {
		*cur_byte++ = true;
		memcpy(cur_byte, &params->ht_capa,
		       sizeof(struct ieee80211_ht_cap));
	} else {
		*cur_byte++ = false;
	}
	cur_byte += sizeof(struct ieee80211_ht_cap);

	put_unaligned_le16(params->sta_flags_mask, cur_byte);
	cur_byte += 2;
	put_unaligned_le16(params->sta_flags_set, cur_byte);
}