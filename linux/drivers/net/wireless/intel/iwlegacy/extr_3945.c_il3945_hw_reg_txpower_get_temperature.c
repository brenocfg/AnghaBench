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
struct il_priv {int last_temperature; scalar_t__ eeprom; } ;
struct il3945_eeprom {TYPE_1__* groups; } ;
struct TYPE_2__ {int temperature; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*,scalar_t__) ; 
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 scalar_t__ IL_TEMP_CONVERT ; 
 int il3945_hw_get_temperature (struct il_priv*) ; 
 scalar_t__ il3945_hw_reg_temp_out_of_range (int) ; 

__attribute__((used)) static int
il3945_hw_reg_txpower_get_temperature(struct il_priv *il)
{
	struct il3945_eeprom *eeprom = (struct il3945_eeprom *)il->eeprom;
	int temperature;

	temperature = il3945_hw_get_temperature(il);

	/* driver's okay range is -260 to +25.
	 *   human readable okay range is 0 to +285 */
	D_INFO("Temperature: %d\n", temperature + IL_TEMP_CONVERT);

	/* handle insane temp reading */
	if (il3945_hw_reg_temp_out_of_range(temperature)) {
		IL_ERR("Error bad temperature value  %d\n", temperature);

		/* if really really hot(?),
		 *   substitute the 3rd band/group's temp measured at factory */
		if (il->last_temperature > 100)
			temperature = eeprom->groups[2].temperature;
		else		/* else use most recent "sane" value from driver */
			temperature = il->last_temperature;
	}

	return temperature;	/* raw, not "human readable" */
}