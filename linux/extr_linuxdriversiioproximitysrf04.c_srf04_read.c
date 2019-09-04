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
typedef  int u64 ;
typedef  int u32 ;
struct srf04_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  ts_rising; int /*<<< orphan*/  ts_falling; int /*<<< orphan*/  falling; int /*<<< orphan*/  rising; int /*<<< orphan*/  gpiod_trig; } ;
typedef  int /*<<< orphan*/  ktime_t ;

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
 int /*<<< orphan*/  udelay (int) ; 
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
	udelay(10);
	gpiod_set_value(data->gpiod_trig, 0);

	/* it cannot take more than 20 ms */
	ret = wait_for_completion_killable_timeout(&data->rising, HZ/50);
	if (ret < 0) {
		mutex_unlock(&data->lock);
		return ret;
	} else if (ret == 0) {
		mutex_unlock(&data->lock);
		return -ETIMEDOUT;
	}

	ret = wait_for_completion_killable_timeout(&data->falling, HZ/50);
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
	 * measuring more than 3 meters is beyond the capabilities of
	 * the sensor
	 * ==> filter out invalid results for not measuring echos of
	 *     another us sensor
	 *
	 * formula:
	 *         distance       3 m
	 * time = ---------- = --------- = 9404389 ns
	 *          speed       319 m/s
	 *
	 * using a minimum speed at -20 °C of 319 m/s
	 */
	if (dt_ns > 9404389)
		return -EIO;

	time_ns = dt_ns;

	/*
	 * the speed as function of the temperature is approximately:
	 *
	 * speed = 331,5 + 0,6 * Temp
	 *   with Temp in °C
	 *   and speed in m/s
	 *
	 * use 343 m/s as ultrasonic speed at 20 °C here in absence of the
	 * temperature
	 *
	 * therefore:
	 *             time     343
	 * distance = ------ * -----
	 *             10^6       2
	 *   with time in ns
	 *   and distance in mm (one way)
	 *
	 * because we limit to 3 meters the multiplication with 343 just
	 * fits into 32 bit
	 */
	distance_mm = time_ns * 343 / 2000000;

	return distance_mm;
}