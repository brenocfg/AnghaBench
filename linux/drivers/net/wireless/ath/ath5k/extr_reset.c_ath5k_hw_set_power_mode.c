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
typedef  int u32 ;
typedef  int u16 ;
struct ath5k_hw {int dummy; } ;
typedef  enum ath5k_power_mode { ____Placeholder_ath5k_power_mode } ath5k_power_mode ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_PCICFG ; 
 int AR5K_PCICFG_SPWR_DN ; 
#define  AR5K_PM_AUTO 131 
#define  AR5K_PM_AWAKE 130 
#define  AR5K_PM_FULL_SLEEP 129 
#define  AR5K_PM_NETWORK_SLEEP 128 
 int /*<<< orphan*/  AR5K_SLEEP_CTL ; 
 int AR5K_SLEEP_CTL_SLE ; 
 int AR5K_SLEEP_CTL_SLE_ALLOW ; 
 int AR5K_SLEEP_CTL_SLE_SLP ; 
 int AR5K_SLEEP_CTL_SLE_WAKE ; 
 int /*<<< orphan*/  AR5K_STA_ID1 ; 
 int AR5K_STA_ID1_DEFAULT_ANTENNA ; 
 int AR5K_STA_ID1_PWR_SV ; 
 int EINVAL ; 
 int EIO ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
ath5k_hw_set_power_mode(struct ath5k_hw *ah, enum ath5k_power_mode mode,
			      bool set_chip, u16 sleep_duration)
{
	unsigned int i;
	u32 staid, data;

	staid = ath5k_hw_reg_read(ah, AR5K_STA_ID1);

	switch (mode) {
	case AR5K_PM_AUTO:
		staid &= ~AR5K_STA_ID1_DEFAULT_ANTENNA;
		/* fallthrough */
	case AR5K_PM_NETWORK_SLEEP:
		if (set_chip)
			ath5k_hw_reg_write(ah,
				AR5K_SLEEP_CTL_SLE_ALLOW |
				sleep_duration,
				AR5K_SLEEP_CTL);

		staid |= AR5K_STA_ID1_PWR_SV;
		break;

	case AR5K_PM_FULL_SLEEP:
		if (set_chip)
			ath5k_hw_reg_write(ah, AR5K_SLEEP_CTL_SLE_SLP,
				AR5K_SLEEP_CTL);

		staid |= AR5K_STA_ID1_PWR_SV;
		break;

	case AR5K_PM_AWAKE:

		staid &= ~AR5K_STA_ID1_PWR_SV;

		if (!set_chip)
			goto commit;

		data = ath5k_hw_reg_read(ah, AR5K_SLEEP_CTL);

		/* If card is down we 'll get 0xffff... so we
		 * need to clean this up before we write the register
		 */
		if (data & 0xffc00000)
			data = 0;
		else
			/* Preserve sleep duration etc */
			data = data & ~AR5K_SLEEP_CTL_SLE;

		ath5k_hw_reg_write(ah, data | AR5K_SLEEP_CTL_SLE_WAKE,
							AR5K_SLEEP_CTL);
		usleep_range(15, 20);

		for (i = 200; i > 0; i--) {
			/* Check if the chip did wake up */
			if ((ath5k_hw_reg_read(ah, AR5K_PCICFG) &
					AR5K_PCICFG_SPWR_DN) == 0)
				break;

			/* Wait a bit and retry */
			usleep_range(50, 75);
			ath5k_hw_reg_write(ah, data | AR5K_SLEEP_CTL_SLE_WAKE,
							AR5K_SLEEP_CTL);
		}

		/* Fail if the chip didn't wake up */
		if (i == 0)
			return -EIO;

		break;

	default:
		return -EINVAL;
	}

commit:
	ath5k_hw_reg_write(ah, staid, AR5K_STA_ID1);

	return 0;
}