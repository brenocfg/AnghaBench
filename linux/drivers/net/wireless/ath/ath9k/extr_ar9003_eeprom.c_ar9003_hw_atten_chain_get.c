#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_8__ {int* xatten1DB; } ;
struct TYPE_7__ {int* xatten1DBLow; int* xatten1DBHigh; } ;
struct TYPE_6__ {int* xatten1DB; } ;
struct ar9300_eeprom {TYPE_4__ modalHeader5G; TYPE_3__ base_ext2; TYPE_2__ modalHeader2G; } ;
struct TYPE_5__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
struct ath9k_channel {scalar_t__ channel; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int ar9003_hw_power_interpolate (int /*<<< orphan*/ ,int*,int*,int) ; 

__attribute__((used)) static u16 ar9003_hw_atten_chain_get(struct ath_hw *ah, int chain,
				     struct ath9k_channel *chan)
{
	int f[3], t[3];
	u16 value;
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	if (chain >= 0 && chain < 3) {
		if (IS_CHAN_2GHZ(chan))
			return eep->modalHeader2G.xatten1DB[chain];
		else if (eep->base_ext2.xatten1DBLow[chain] != 0) {
			t[0] = eep->base_ext2.xatten1DBLow[chain];
			f[0] = 5180;
			t[1] = eep->modalHeader5G.xatten1DB[chain];
			f[1] = 5500;
			t[2] = eep->base_ext2.xatten1DBHigh[chain];
			f[2] = 5785;
			value = ar9003_hw_power_interpolate((s32) chan->channel,
							    f, t, 3);
			return value;
		} else
			return eep->modalHeader5G.xatten1DB[chain];
	}

	return 0;
}