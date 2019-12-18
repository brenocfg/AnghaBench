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
struct il_priv {int dummy; } ;
struct ieee80211_rate {int bitrate; int hw_value; int hw_value_short; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int ieee; int plcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RATE_SHORT_PREAMBLE ; 
 int IL39_LAST_OFDM_RATE ; 
 int IL_FIRST_OFDM_RATE ; 
 int RATE_COUNT_LEGACY ; 
 TYPE_1__* il3945_rates ; 

__attribute__((used)) static void
il3945_init_hw_rates(struct il_priv *il, struct ieee80211_rate *rates)
{
	int i;

	for (i = 0; i < RATE_COUNT_LEGACY; i++) {
		rates[i].bitrate = il3945_rates[i].ieee * 5;
		rates[i].hw_value = i;	/* Rate scaling will work on idxes */
		rates[i].hw_value_short = i;
		rates[i].flags = 0;
		if (i > IL39_LAST_OFDM_RATE || i < IL_FIRST_OFDM_RATE) {
			/*
			 * If CCK != 1M then set short preamble rate flag.
			 */
			rates[i].flags |=
			    (il3945_rates[i].plcp ==
			     10) ? 0 : IEEE80211_RATE_SHORT_PREAMBLE;
		}
	}
}