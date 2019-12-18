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
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  version; } ;
struct TYPE_5__ {TYPE_1__ baseEepHeader; } ;
struct TYPE_6__ {TYPE_2__ map4k; } ;
struct ath_hw {TYPE_3__ eeprom; } ;

/* Variables and functions */
 int AR5416_EEP_VER_MINOR_MASK ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_hw_4k_get_eeprom_rev(struct ath_hw *ah)
{
	u16 version = le16_to_cpu(ah->eeprom.map4k.baseEepHeader.version);

	return version & AR5416_EEP_VER_MINOR_MASK;
}