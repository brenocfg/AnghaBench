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
struct qpnp_tm_chip {scalar_t__ subtype; unsigned int stage; unsigned int temp; unsigned int thresh; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ QPNP_TM_SUBTYPE_GEN1 ; 
 unsigned int TEMP_STAGE_HYSTERESIS ; 
 unsigned int TEMP_STAGE_STEP ; 
 unsigned int TEMP_THRESH_MIN ; 
 unsigned int TEMP_THRESH_STEP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int* alarm_state_map ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int qpnp_tm_get_temp_stage (struct qpnp_tm_chip*) ; 

__attribute__((used)) static int qpnp_tm_update_temp_no_adc(struct qpnp_tm_chip *chip)
{
	unsigned int stage, stage_new, stage_old;
	int ret;

	WARN_ON(!mutex_is_locked(&chip->lock));

	ret = qpnp_tm_get_temp_stage(chip);
	if (ret < 0)
		return ret;
	stage = ret;

	if (chip->subtype == QPNP_TM_SUBTYPE_GEN1) {
		stage_new = stage;
		stage_old = chip->stage;
	} else {
		stage_new = alarm_state_map[stage];
		stage_old = alarm_state_map[chip->stage];
	}

	if (stage_new > stage_old) {
		/* increasing stage, use lower bound */
		chip->temp = (stage_new - 1) * TEMP_STAGE_STEP +
			     chip->thresh * TEMP_THRESH_STEP +
			     TEMP_STAGE_HYSTERESIS + TEMP_THRESH_MIN;
	} else if (stage_new < stage_old) {
		/* decreasing stage, use upper bound */
		chip->temp = stage_new * TEMP_STAGE_STEP +
			     chip->thresh * TEMP_THRESH_STEP -
			     TEMP_STAGE_HYSTERESIS + TEMP_THRESH_MIN;
	}

	chip->stage = stage;

	return 0;
}