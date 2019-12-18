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
typedef  scalar_t__ u8 ;
struct mt7603_dev {int reset_test; int cur_reset_cause; int /*<<< orphan*/ * reset_cause; } ;
typedef  enum mt7603_reset_cause { ____Placeholder_mt7603_reset_cause } mt7603_reset_cause ;

/* Variables and functions */
 scalar_t__ MT7603_WATCHDOG_TIMEOUT ; 

__attribute__((used)) static bool
mt7603_watchdog_check(struct mt7603_dev *dev, u8 *counter,
		      enum mt7603_reset_cause cause,
		      bool (*check)(struct mt7603_dev *dev))
{
	if (dev->reset_test == cause + 1) {
		dev->reset_test = 0;
		goto trigger;
	}

	if (check) {
		if (!check(dev) && *counter < MT7603_WATCHDOG_TIMEOUT) {
			*counter = 0;
			return false;
		}

		(*counter)++;
	}

	if (*counter < MT7603_WATCHDOG_TIMEOUT)
		return false;
trigger:
	dev->cur_reset_cause = cause;
	dev->reset_cause[cause]++;
	return true;
}