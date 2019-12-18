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
typedef  int u64 ;
typedef  int u32 ;
struct srf04_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  ts_rising; int /*<<< orphan*/  ts_falling; int /*<<< orphan*/  falling; int /*<<< orphan*/  rising; int /*<<< orphan*/  gpiod_trig; TYPE_1__* cfg; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  trigger_pulse_us; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int wait_for_completion_killable_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int srf04_read(struct srf04_data *data)
{
	int ret;
	ktime_t ktime_dt;
	u64 dt_ns;
	u32 time_ns, distance_mm;

	/*
	 * just one read-echo-cycle can take place at a time
	 * ==> lock against concurrent reading calls
	 */
	mutex_lock(&data->lock);

	reinit_completion(&data->rising);
	reinit_completion(&data->falling);

	gpiod_set_value(data->gpiod_trig, 1);
	udelay(data->cfg->trigger_pulse_us);
	gpiod_set_value(data->gpiod_trig, 0);

	/* it should not take more than 20 ms until echo is rising */
	ret = wait_for_completion_killable_timeout(&data->rising, HZ/50);
	if (ret < 0) {
		mutex_unlock(&data->lock);
		return ret;
	} else if (ret == 0) {
		mutex_unlock(&data->lock);
		return -ETIMEDOUT;
	}

	/* it cannot take more than 50 ms until echo is falling */
	ret = wait_for_completion_killable_timeout(&data->falling, HZ/20);
	if (ret < 0) {
		mutex_unlock(&data->lock);
		return ret;
	} else if (ret == 0) {
		mutex_unlock(&data->lock);
		return -ETIMEDOUT;
	}

	ktime_dt = ktime_sub(data->ts_falling, data->ts_rising);

	mutex_unlock(&data->lock);

	dt_ns = ktime_to_ns(ktime_dt);
	/*
	 * measuring more than 6,45 meters is beyond the capabilities of
	 * the supported sensors
	 * ==> filter out invalid results for not measuring echos of
	 *     another us sensor
	 *
	 * formula:
	 *         distance     6,45 * 2 m
	 * time = ---------- = ------------ = 40438871 ns
	 *          speed         319 m/s
	 *
	 * using a minimum speed at -20 °C of 319 m/s
	 */
	if (dt_ns > 40438871)
		return -EIO;

	time_ns = dt_ns;

	/*
	 * the speed as function of the temperature is approximately:
	 *
	 * speed = 331,5 + 0,6 * Temp
	 *   with Temp in °C
	 *   and speed in m/s
	 *
	 * use 343,5 m/s as ultrasonic speed at 20 °C here in absence of the
	 * temperature
	 *
	 * therefore:
	 *             time     343,5     time * 106
	 * distance = ------ * ------- = ------------
	 *             10^6         2         617176
	 *   with time in ns
	 *   and distance in mm (one way)
	 *
	 * because we limit to 6,45 meters the multiplication with 106 just
	 * fits into 32 bit
	 */
	distance_mm = time_ns * 106 / 617176;

	return distance_mm;
}