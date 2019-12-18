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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct cfg80211_wowlan {size_t n_patterns; scalar_t__ four_way_handshake; scalar_t__ eap_identity_req; scalar_t__ gtk_rekey_failure; scalar_t__ magic_pkt; scalar_t__ disconnect; TYPE_1__* patterns; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;
typedef  int /*<<< orphan*/  mask ;
struct TYPE_2__ {int pattern_len; int* mask; int /*<<< orphan*/  pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  WOW_FILTER_OPTION_8021X_4WAYHS ; 
 int /*<<< orphan*/  WOW_FILTER_OPTION_EAP_REQ ; 
 int /*<<< orphan*/  WOW_FILTER_OPTION_GTK_ERROR ; 
 int /*<<< orphan*/  WOW_FILTER_OPTION_MAGIC_PACKET ; 
 int /*<<< orphan*/  WOW_FILTER_OPTION_NWK_DISASSOC ; 
 int /*<<< orphan*/  WOW_LIST_ID ; 
 int WOW_PATTERN_SIZE ; 
 int ath6kl_wmi_add_wow_pattern_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath6kl_wow_usr(struct ath6kl *ar, struct ath6kl_vif *vif,
			  struct cfg80211_wowlan *wow, u32 *filter)
{
	int ret, pos;
	u8 mask[WOW_PATTERN_SIZE];
	u16 i;

	/* Configure the patterns that we received from the user. */
	for (i = 0; i < wow->n_patterns; i++) {
		/*
		 * Convert given nl80211 specific mask value to equivalent
		 * driver specific mask value and send it to the chip along
		 * with patterns. For example, If the mask value defined in
		 * struct cfg80211_wowlan is 0xA (equivalent binary is 1010),
		 * then equivalent driver specific mask value is
		 * "0xFF 0x00 0xFF 0x00".
		 */
		memset(&mask, 0, sizeof(mask));
		for (pos = 0; pos < wow->patterns[i].pattern_len; pos++) {
			if (wow->patterns[i].mask[pos / 8] & (0x1 << (pos % 8)))
				mask[pos] = 0xFF;
		}
		/*
		 * Note: Pattern's offset is not passed as part of wowlan
		 * parameter from CFG layer. So it's always passed as ZERO
		 * to the firmware. It means, given WOW patterns are always
		 * matched from the first byte of received pkt in the firmware.
		 */
		ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
				vif->fw_vif_idx, WOW_LIST_ID,
				wow->patterns[i].pattern_len,
				0 /* pattern offset */,
				wow->patterns[i].pattern, mask);
		if (ret)
			return ret;
	}

	if (wow->disconnect)
		*filter |= WOW_FILTER_OPTION_NWK_DISASSOC;

	if (wow->magic_pkt)
		*filter |= WOW_FILTER_OPTION_MAGIC_PACKET;

	if (wow->gtk_rekey_failure)
		*filter |= WOW_FILTER_OPTION_GTK_ERROR;

	if (wow->eap_identity_req)
		*filter |= WOW_FILTER_OPTION_EAP_REQ;

	if (wow->four_way_handshake)
		*filter |= WOW_FILTER_OPTION_8021X_4WAYHS;

	return 0;
}