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
struct ath_hw {int /*<<< orphan*/  imask; } ;
struct ath_common {int dummy; } ;
struct ath_beacon_config {int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  intval; int /*<<< orphan*/  nexttbtt; scalar_t__ enable_beacon; scalar_t__ ibss_creator; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_INT_SWBA ; 
 int /*<<< orphan*/  BEACON ; 
 int /*<<< orphan*/  TU_TO_USEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_get_next_tbtt (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_gettsf64 (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath9k_cmn_beacon_config_adhoc(struct ath_hw *ah,
				   struct ath_beacon_config *conf)
{
	struct ath_common *common = ath9k_hw_common(ah);

	conf->intval = TU_TO_USEC(conf->beacon_interval);

	if (conf->ibss_creator)
		conf->nexttbtt = conf->intval;
	else
		conf->nexttbtt = ath9k_get_next_tbtt(ah, ath9k_hw_gettsf64(ah),
					       conf->beacon_interval);

	if (conf->enable_beacon)
		ah->imask |= ATH9K_INT_SWBA;
	else
		ah->imask &= ~ATH9K_INT_SWBA;

	ath_dbg(common, BEACON,
		"IBSS (%s) nexttbtt: %u intval: %u conf_intval: %u\n",
		(conf->enable_beacon) ? "Enable" : "Disable",
		conf->nexttbtt, conf->intval, conf->beacon_interval);
}