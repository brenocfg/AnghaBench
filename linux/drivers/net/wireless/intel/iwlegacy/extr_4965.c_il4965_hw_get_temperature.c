#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int /*<<< orphan*/  temperature; } ;
struct TYPE_8__ {TYPE_2__ common; } ;
struct TYPE_9__ {int flag; TYPE_3__ general; } ;
struct TYPE_10__ {TYPE_4__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/ * therm_r4; int /*<<< orphan*/ * therm_r3; int /*<<< orphan*/ * therm_r2; int /*<<< orphan*/ * therm_r1; } ;
struct il_priv {TYPE_5__ _4965; int /*<<< orphan*/  status; TYPE_1__ card_alive_init; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_TEMP (char*,...) ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  KELVIN_TO_CELSIUS (scalar_t__) ; 
 int STATS_REPLY_FLG_HT40_MODE_MSK ; 
 int /*<<< orphan*/  S_TEMPERATURE ; 
 scalar_t__ TEMPERATURE_CALIB_A_VAL ; 
 scalar_t__ TEMPERATURE_CALIB_KELVIN_OFFSET ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ sign_extend32 (scalar_t__,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il4965_hw_get_temperature(struct il_priv *il)
{
	s32 temperature;
	s32 vt;
	s32 R1, R2, R3;
	u32 R4;

	if (test_bit(S_TEMPERATURE, &il->status) &&
	    (il->_4965.stats.flag & STATS_REPLY_FLG_HT40_MODE_MSK)) {
		D_TEMP("Running HT40 temperature calibration\n");
		R1 = (s32) le32_to_cpu(il->card_alive_init.therm_r1[1]);
		R2 = (s32) le32_to_cpu(il->card_alive_init.therm_r2[1]);
		R3 = (s32) le32_to_cpu(il->card_alive_init.therm_r3[1]);
		R4 = le32_to_cpu(il->card_alive_init.therm_r4[1]);
	} else {
		D_TEMP("Running temperature calibration\n");
		R1 = (s32) le32_to_cpu(il->card_alive_init.therm_r1[0]);
		R2 = (s32) le32_to_cpu(il->card_alive_init.therm_r2[0]);
		R3 = (s32) le32_to_cpu(il->card_alive_init.therm_r3[0]);
		R4 = le32_to_cpu(il->card_alive_init.therm_r4[0]);
	}

	/*
	 * Temperature is only 23 bits, so sign extend out to 32.
	 *
	 * NOTE If we haven't received a stats notification yet
	 * with an updated temperature, use R4 provided to us in the
	 * "initialize" ALIVE response.
	 */
	if (!test_bit(S_TEMPERATURE, &il->status))
		vt = sign_extend32(R4, 23);
	else
		vt = sign_extend32(le32_to_cpu
				   (il->_4965.stats.general.common.temperature),
				   23);

	D_TEMP("Calib values R[1-3]: %d %d %d R4: %d\n", R1, R2, R3, vt);

	if (R3 == R1) {
		IL_ERR("Calibration conflict R1 == R3\n");
		return -1;
	}

	/* Calculate temperature in degrees Kelvin, adjust by 97%.
	 * Add offset to center the adjustment around 0 degrees Centigrade. */
	temperature = TEMPERATURE_CALIB_A_VAL * (vt - R2);
	temperature /= (R3 - R1);
	temperature =
	    (temperature * 97) / 100 + TEMPERATURE_CALIB_KELVIN_OFFSET;

	D_TEMP("Calibrated temperature: %dK, %dC\n", temperature,
	       KELVIN_TO_CELSIUS(temperature));

	return temperature;
}