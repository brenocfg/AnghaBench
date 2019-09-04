#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bh1770_chip {int lux_wait_result; int int_mode_prox; size_t prox_rate_threshold; int int_mode_lux; int /*<<< orphan*/  prox_work; int /*<<< orphan*/  mutex; TYPE_2__* client; int /*<<< orphan*/  lux_threshold_lo; int /*<<< orphan*/  lux_threshold_hi; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH1770_ALS_PS_STATUS ; 
 int /*<<< orphan*/  BH1770_INTERRUPT ; 
 int BH1770_INT_ALS_DATA ; 
 int BH1770_INT_ALS_INT ; 
 int BH1770_INT_LEDS_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bh1770_lux_get_result (struct bh1770_chip*) ; 
 int /*<<< orphan*/  bh1770_lux_update_thresholds (struct bh1770_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh1770_prox_read_result (struct bh1770_chip*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int i2c_smbus_read_byte_data (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* prox_rates_ms ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bh1770_irq(int irq, void *data)
{
	struct bh1770_chip *chip = data;
	int status;
	int rate = 0;

	mutex_lock(&chip->mutex);
	status = i2c_smbus_read_byte_data(chip->client, BH1770_ALS_PS_STATUS);

	/* Acknowledge interrupt by reading this register */
	i2c_smbus_read_byte_data(chip->client, BH1770_INTERRUPT);

	/*
	 * Check if there is fresh data available for als.
	 * If this is the very first data, update thresholds after that.
	 */
	if (status & BH1770_INT_ALS_DATA) {
		bh1770_lux_get_result(chip);
		if (unlikely(chip->lux_wait_result)) {
			chip->lux_wait_result = false;
			wake_up(&chip->wait);
			bh1770_lux_update_thresholds(chip,
						chip->lux_threshold_hi,
						chip->lux_threshold_lo);
		}
	}

	/* Disable interrupt logic to guarantee acknowledgement */
	i2c_smbus_write_byte_data(chip->client, BH1770_INTERRUPT,
				  (0 << 1) | (0 << 0));

	if ((status & BH1770_INT_ALS_INT))
		sysfs_notify(&chip->client->dev.kobj, NULL, "lux0_input");

	if (chip->int_mode_prox && (status & BH1770_INT_LEDS_INT)) {
		rate = prox_rates_ms[chip->prox_rate_threshold];
		bh1770_prox_read_result(chip);
	}

	/* Re-enable interrupt logic */
	i2c_smbus_write_byte_data(chip->client, BH1770_INTERRUPT,
				  (chip->int_mode_lux << 1) |
				  (chip->int_mode_prox << 0));
	mutex_unlock(&chip->mutex);

	/*
	 * Can't cancel work while keeping mutex since the work uses the
	 * same mutex.
	 */
	if (rate) {
		/*
		 * Simulate missing no-proximity interrupt 50ms after the
		 * next expected interrupt time.
		 */
		cancel_delayed_work_sync(&chip->prox_work);
		schedule_delayed_work(&chip->prox_work,
				msecs_to_jiffies(rate + 50));
	}
	return IRQ_HANDLED;
}