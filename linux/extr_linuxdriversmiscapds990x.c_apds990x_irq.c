#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct apds990x_chip {scalar_t__ lux_clear; scalar_t__ lux_ir; scalar_t__ again_meas; scalar_t__ again_next; int lux_wait_fresh_res; scalar_t__ a_max_result; scalar_t__ prox_data; scalar_t__ prox_thres; int /*<<< orphan*/  mutex; TYPE_1__* client; int /*<<< orphan*/  prox_continuous_mode; scalar_t__ prox_en; int /*<<< orphan*/  wait; int /*<<< orphan*/  lux_raw; int /*<<< orphan*/  lux; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS990X_CDATAL ; 
 int /*<<< orphan*/  APDS990X_IRDATAL ; 
 int /*<<< orphan*/  APDS990X_PDATAL ; 
 int /*<<< orphan*/  APDS990X_STATUS ; 
 int APDS990X_ST_AINT ; 
 int APDS990X_ST_PINT ; 
 scalar_t__ APDS_PROX_RANGE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  apds990x_ack_int (struct apds990x_chip*,int) ; 
 scalar_t__ apds990x_calc_again (struct apds990x_chip*) ; 
 int /*<<< orphan*/  apds990x_get_lux (struct apds990x_chip*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  apds990x_read_byte (struct apds990x_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  apds990x_read_word (struct apds990x_chip*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  apds990x_refresh_pthres (struct apds990x_chip*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t apds990x_irq(int irq, void *data)
{
	struct apds990x_chip *chip = data;
	u8 status;

	apds990x_read_byte(chip, APDS990X_STATUS, &status);
	apds990x_ack_int(chip, status);

	mutex_lock(&chip->mutex);
	if (!pm_runtime_suspended(&chip->client->dev)) {
		if (status & APDS990X_ST_AINT) {
			apds990x_read_word(chip, APDS990X_CDATAL,
					&chip->lux_clear);
			apds990x_read_word(chip, APDS990X_IRDATAL,
					&chip->lux_ir);
			/* Store used gain for calculations */
			chip->again_meas = chip->again_next;

			chip->lux_raw = apds990x_get_lux(chip,
							chip->lux_clear,
							chip->lux_ir);

			if (apds990x_calc_again(chip) == 0) {
				/* Result is valid */
				chip->lux = chip->lux_raw;
				chip->lux_wait_fresh_res = false;
				wake_up(&chip->wait);
				sysfs_notify(&chip->client->dev.kobj,
					NULL, "lux0_input");
			}
		}

		if ((status & APDS990X_ST_PINT) && chip->prox_en) {
			u16 clr_ch;

			apds990x_read_word(chip, APDS990X_CDATAL, &clr_ch);
			/*
			 * If ALS channel is saturated at min gain,
			 * proximity gives false posivite values.
			 * Just ignore them.
			 */
			if (chip->again_meas == 0 &&
				clr_ch == chip->a_max_result)
				chip->prox_data = 0;
			else
				apds990x_read_word(chip,
						APDS990X_PDATAL,
						&chip->prox_data);

			apds990x_refresh_pthres(chip, chip->prox_data);
			if (chip->prox_data < chip->prox_thres)
				chip->prox_data = 0;
			else if (!chip->prox_continuous_mode)
				chip->prox_data = APDS_PROX_RANGE;
			sysfs_notify(&chip->client->dev.kobj,
				NULL, "prox0_raw");
		}
	}
	mutex_unlock(&chip->mutex);
	return IRQ_HANDLED;
}