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
typedef  int u8 ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int IEEE80211_QOS_CTL_A_MSDU_PRESENT ; 
 unsigned int NET_IP_ALIGN ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_has_a4 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int _rtl_rx_get_padding(struct ieee80211_hdr *hdr,
					unsigned int len)
{
#if NET_IP_ALIGN != 0
	unsigned int padding = 0;
#endif

	/* make function no-op when possible */
	if (NET_IP_ALIGN == 0 || len < sizeof(*hdr))
		return 0;

#if NET_IP_ALIGN != 0
	/* alignment calculation as in lbtf_rx() / carl9170_rx_copy_data() */
	/* TODO: deduplicate common code, define helper function instead? */

	if (ieee80211_is_data_qos(hdr->frame_control)) {
		u8 *qc = ieee80211_get_qos_ctl(hdr);

		padding ^= NET_IP_ALIGN;

		/* Input might be invalid, avoid accessing memory outside
		 * the buffer.
		 */
		if ((unsigned long)qc - (unsigned long)hdr < len &&
		    *qc & IEEE80211_QOS_CTL_A_MSDU_PRESENT)
			padding ^= NET_IP_ALIGN;
	}

	if (ieee80211_has_a4(hdr->frame_control))
		padding ^= NET_IP_ALIGN;

	return padding;
#endif
}