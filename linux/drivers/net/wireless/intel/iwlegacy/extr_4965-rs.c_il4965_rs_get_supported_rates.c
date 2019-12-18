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
typedef  int /*<<< orphan*/  u16 ;
struct il_lq_sta {int /*<<< orphan*/  active_mimo2_rate; int /*<<< orphan*/  active_siso_rate; int /*<<< orphan*/  active_legacy_rate; } ;
struct ieee80211_hdr {int dummy; } ;
typedef  enum il_table_type { ____Placeholder_il_table_type } il_table_type ;

/* Variables and functions */
 scalar_t__ is_legacy (int) ; 
 scalar_t__ is_siso (int) ; 

__attribute__((used)) static u16
il4965_rs_get_supported_rates(struct il_lq_sta *lq_sta,
			      struct ieee80211_hdr *hdr,
			      enum il_table_type rate_type)
{
	if (is_legacy(rate_type)) {
		return lq_sta->active_legacy_rate;
	} else {
		if (is_siso(rate_type))
			return lq_sta->active_siso_rate;
		else
			return lq_sta->active_mimo2_rate;
	}
}