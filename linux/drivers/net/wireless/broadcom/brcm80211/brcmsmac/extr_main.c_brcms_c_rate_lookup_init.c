#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  int u8 ;
struct brcms_c_rateset {size_t count; int* rates; } ;
struct brcms_c_info {TYPE_3__* band; TYPE_1__* hw; } ;
struct TYPE_5__ {size_t count; int* rates; } ;
struct TYPE_6__ {int* basic_rate; TYPE_2__ hw_rateset; } ;
struct TYPE_4__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int BRCMS_RATE_FLAG ; 
 int BRCMS_RATE_MASK ; 
 int BRCM_MAXRATE ; 
 int BRCM_RATE_12M ; 
 int BRCM_RATE_24M ; 
 int BRCM_RATE_6M ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_ofdm_rate (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcms_c_rate_lookup_init(struct brcms_c_info *wlc,
			      struct brcms_c_rateset *rateset)
{
	u8 rate;
	u8 mandatory;
	u8 cck_basic = 0;
	u8 ofdm_basic = 0;
	u8 *br = wlc->band->basic_rate;
	uint i;

	/* incoming rates are in 500kbps units as in 802.11 Supported Rates */
	memset(br, 0, BRCM_MAXRATE + 1);

	/* For each basic rate in the rates list, make an entry in the
	 * best basic lookup.
	 */
	for (i = 0; i < rateset->count; i++) {
		/* only make an entry for a basic rate */
		if (!(rateset->rates[i] & BRCMS_RATE_FLAG))
			continue;

		/* mask off basic bit */
		rate = (rateset->rates[i] & BRCMS_RATE_MASK);

		if (rate > BRCM_MAXRATE) {
			brcms_err(wlc->hw->d11core, "brcms_c_rate_lookup_init: "
				  "invalid rate 0x%X in rate set\n",
				  rateset->rates[i]);
			continue;
		}

		br[rate] = rate;
	}

	/* The rate lookup table now has non-zero entries for each
	 * basic rate, equal to the basic rate: br[basicN] = basicN
	 *
	 * To look up the best basic rate corresponding to any
	 * particular rate, code can use the basic_rate table
	 * like this
	 *
	 * basic_rate = wlc->band->basic_rate[tx_rate]
	 *
	 * Make sure there is a best basic rate entry for
	 * every rate by walking up the table from low rates
	 * to high, filling in holes in the lookup table
	 */

	for (i = 0; i < wlc->band->hw_rateset.count; i++) {
		rate = wlc->band->hw_rateset.rates[i];

		if (br[rate] != 0) {
			/* This rate is a basic rate.
			 * Keep track of the best basic rate so far by
			 * modulation type.
			 */
			if (is_ofdm_rate(rate))
				ofdm_basic = rate;
			else
				cck_basic = rate;

			continue;
		}

		/* This rate is not a basic rate so figure out the
		 * best basic rate less than this rate and fill in
		 * the hole in the table
		 */

		br[rate] = is_ofdm_rate(rate) ? ofdm_basic : cck_basic;

		if (br[rate] != 0)
			continue;

		if (is_ofdm_rate(rate)) {
			/*
			 * In 11g and 11a, the OFDM mandatory rates
			 * are 6, 12, and 24 Mbps
			 */
			if (rate >= BRCM_RATE_24M)
				mandatory = BRCM_RATE_24M;
			else if (rate >= BRCM_RATE_12M)
				mandatory = BRCM_RATE_12M;
			else
				mandatory = BRCM_RATE_6M;
		} else {
			/* In 11b, all CCK rates are mandatory 1 - 11 Mbps */
			mandatory = rate;
		}

		br[rate] = mandatory;
	}
}