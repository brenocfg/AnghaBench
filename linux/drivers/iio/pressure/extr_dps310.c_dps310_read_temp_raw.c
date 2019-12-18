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
struct dps310_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPS310_MEAS_CFG ; 
 int /*<<< orphan*/  DPS310_POLL_SLEEP_US (int) ; 
 int DPS310_POLL_TIMEOUT_US (int) ; 
 int DPS310_TMP_RDY ; 
 int EINTR ; 
 int dps310_get_temp_samp_freq (struct dps310_data*) ; 
 int dps310_read_temp_ready (struct dps310_data*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dps310_read_temp_raw(struct dps310_data *data)
{
	int rc;
	int rate;
	int ready;
	int timeout;

	if (mutex_lock_interruptible(&data->lock))
		return -EINTR;

	rate = dps310_get_temp_samp_freq(data);
	timeout = DPS310_POLL_TIMEOUT_US(rate);

	/* Poll for sensor readiness; base the timeout upon the sample rate. */
	rc = regmap_read_poll_timeout(data->regmap, DPS310_MEAS_CFG, ready,
				      ready & DPS310_TMP_RDY,
				      DPS310_POLL_SLEEP_US(timeout), timeout);
	if (rc < 0)
		goto done;

	rc = dps310_read_temp_ready(data);

done:
	mutex_unlock(&data->lock);
	return rc;
}