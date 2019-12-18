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
struct ath_hw {int dummy; } ;
struct ath_common {TYPE_1__* bus_ops; } ;
struct TYPE_2__ {scalar_t__ ath_bus_type; } ;

/* Variables and functions */
 scalar_t__ ATH_USB ; 
 int /*<<< orphan*/  EEPROM ; 
 int __ath9k_hw_4k_fill_eeprom (struct ath_hw*) ; 
 int __ath9k_hw_usb_4k_fill_eeprom (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_use_flash (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool ath9k_hw_4k_fill_eeprom(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	if (!ath9k_hw_use_flash(ah)) {
		ath_dbg(common, EEPROM, "Reading from EEPROM, not flash\n");
	}

	if (common->bus_ops->ath_bus_type == ATH_USB)
		return __ath9k_hw_usb_4k_fill_eeprom(ah);
	else
		return __ath9k_hw_4k_fill_eeprom(ah);
}