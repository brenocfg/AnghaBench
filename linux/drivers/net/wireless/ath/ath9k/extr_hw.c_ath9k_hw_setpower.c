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
struct ath_hw {int power_mode; int chip_fullsleep; int ah_flags; } ;
struct ath_common {int dummy; } ;
typedef  enum ath9k_power_mode { ____Placeholder_ath9k_power_mode } ath9k_power_mode ;

/* Variables and functions */
 int AH_UNPLUGGED ; 
#define  ATH9K_PM_AWAKE 130 
#define  ATH9K_PM_FULL_SLEEP 129 
#define  ATH9K_PM_NETWORK_SLEEP 128 
 int /*<<< orphan*/  ATH_DBG_WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  ar9003_mci_set_full_sleep (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int ath9k_hw_set_power_awake (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_set_power_network_sleep (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_set_power_sleep (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int) ; 

bool ath9k_hw_setpower(struct ath_hw *ah, enum ath9k_power_mode mode)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int status = true;
	static const char *modes[] = {
		"AWAKE",
		"FULL-SLEEP",
		"NETWORK SLEEP",
		"UNDEFINED"
	};

	if (ah->power_mode == mode)
		return status;

	ath_dbg(common, RESET, "%s -> %s\n",
		modes[ah->power_mode], modes[mode]);

	switch (mode) {
	case ATH9K_PM_AWAKE:
		status = ath9k_hw_set_power_awake(ah);
		break;
	case ATH9K_PM_FULL_SLEEP:
		if (ath9k_hw_mci_is_enabled(ah))
			ar9003_mci_set_full_sleep(ah);

		ath9k_set_power_sleep(ah);
		ah->chip_fullsleep = true;
		break;
	case ATH9K_PM_NETWORK_SLEEP:
		ath9k_set_power_network_sleep(ah);
		break;
	default:
		ath_err(common, "Unknown power mode %u\n", mode);
		return false;
	}
	ah->power_mode = mode;

	/*
	 * XXX: If this warning never comes up after a while then
	 * simply keep the ATH_DBG_WARN_ON_ONCE() but make
	 * ath9k_hw_setpower() return type void.
	 */

	if (!(ah->ah_flags & AH_UNPLUGGED))
		ATH_DBG_WARN_ON_ONCE(!status);

	return status;
}