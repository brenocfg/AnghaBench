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
struct ieee80211_supported_band {int band; void* n_bitrates; int /*<<< orphan*/ * bitrates; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
#define  NL80211_BAND_2GHZ 129 
#define  NL80211_BAND_5GHZ 128 
 void* qtnf_rates_2g ; 
 void* qtnf_rates_5g ; 

void qtnf_band_init_rates(struct ieee80211_supported_band *band)
{
	switch (band->band) {
	case NL80211_BAND_2GHZ:
		band->bitrates = qtnf_rates_2g;
		band->n_bitrates = ARRAY_SIZE(qtnf_rates_2g);
		break;
	case NL80211_BAND_5GHZ:
		band->bitrates = qtnf_rates_5g;
		band->n_bitrates = ARRAY_SIZE(qtnf_rates_5g);
		break;
	default:
		band->bitrates = NULL;
		band->n_bitrates = 0;
		break;
	}
}