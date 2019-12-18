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
struct cfg80211_pkt_pattern {int* mask; int /*<<< orphan*/  pkt_offset; int /*<<< orphan*/ * pattern; int /*<<< orphan*/  pattern_len; } ;
typedef  int s8 ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
mwifiex_is_pattern_supported(struct cfg80211_pkt_pattern *pat, s8 *byte_seq,
			     u8 max_byte_seq)
{
	int j, k, valid_byte_cnt = 0;
	bool dont_care_byte = false;

	for (j = 0; j < DIV_ROUND_UP(pat->pattern_len, 8); j++) {
		for (k = 0; k < 8; k++) {
			if (pat->mask[j] & 1 << k) {
				memcpy(byte_seq + valid_byte_cnt,
				       &pat->pattern[j * 8 + k], 1);
				valid_byte_cnt++;
				if (dont_care_byte)
					return false;
			} else {
				if (valid_byte_cnt)
					dont_care_byte = true;
			}

			/* wildcard bytes record as the offset
			 * before the valid byte
			 */
			if (!valid_byte_cnt && !dont_care_byte)
				pat->pkt_offset++;

			if (valid_byte_cnt > max_byte_seq)
				return false;
		}
	}

	byte_seq[max_byte_seq] = valid_byte_cnt;

	return true;
}