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
struct ath_hw {TYPE_1__* eep_ops; } ;
struct ath9k_channel {int dummy; } ;
typedef  enum eeprom_param { ____Placeholder_eeprom_param } eeprom_param ;
struct TYPE_2__ {int (* get_eeprom ) (struct ath_hw*,int) ;} ;

/* Variables and functions */
 int EEP_ANTENNA_GAIN_2G ; 
 int EEP_ANTENNA_GAIN_5G ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int stub1 (struct ath_hw*,int) ; 

__attribute__((used)) static int get_antenna_gain(struct ath_hw *ah, struct ath9k_channel *chan)
{
	enum eeprom_param gain_param;

	if (IS_CHAN_2GHZ(chan))
		gain_param = EEP_ANTENNA_GAIN_2G;
	else
		gain_param = EEP_ANTENNA_GAIN_5G;

	return ah->eep_ops->get_eeprom(ah, gain_param);
}