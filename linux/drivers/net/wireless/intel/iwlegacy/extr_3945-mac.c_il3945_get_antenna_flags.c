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
struct il_priv {scalar_t__ eeprom; } ;
struct il3945_eeprom {int /*<<< orphan*/  antenna_switch_type; } ;
typedef  int __le32 ;
struct TYPE_2__ {int antenna; } ;

/* Variables and functions */
#define  IL_ANTENNA_AUX 130 
#define  IL_ANTENNA_DIVERSITY 129 
#define  IL_ANTENNA_MAIN 128 
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int RXON_FLG_ANT_A_MSK ; 
 int RXON_FLG_ANT_B_MSK ; 
 int RXON_FLG_DIS_DIV_MSK ; 
 TYPE_1__ il3945_mod_params ; 

__le32
il3945_get_antenna_flags(const struct il_priv *il)
{
	struct il3945_eeprom *eeprom = (struct il3945_eeprom *)il->eeprom;

	switch (il3945_mod_params.antenna) {
	case IL_ANTENNA_DIVERSITY:
		return 0;

	case IL_ANTENNA_MAIN:
		if (eeprom->antenna_switch_type)
			return RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_B_MSK;
		return RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_A_MSK;

	case IL_ANTENNA_AUX:
		if (eeprom->antenna_switch_type)
			return RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_A_MSK;
		return RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_B_MSK;
	}

	/* bad antenna selector value */
	IL_ERR("Bad antenna selector value (0x%x)\n",
	       il3945_mod_params.antenna);

	return 0;		/* "diversity" is default if error */
}