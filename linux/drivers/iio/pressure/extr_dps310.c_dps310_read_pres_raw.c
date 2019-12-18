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
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
struct dps310_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  pressure_raw; int /*<<< orphan*/  regmap; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DPS310_MEAS_CFG ; 
 int /*<<< orphan*/  DPS310_POLL_SLEEP_US (int) ; 
 int DPS310_POLL_TIMEOUT_US (int) ; 
 int /*<<< orphan*/  DPS310_PRS_BASE ; 
 int DPS310_PRS_RDY ; 
 int EINTR ; 
 int dps310_get_pres_samp_freq (struct dps310_data*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sign_extend32 (int,int) ; 

__attribute__((used)) static int dps310_read_pres_raw(struct dps310_data *data)
{
	int rc;
	int rate;
	int ready;
	int timeout;
	s32 raw;
	u8 val[3];

	if (mutex_lock_interruptible(&data->lock))
		return -EINTR;

	rate = dps310_get_pres_samp_freq(data);
	timeout = DPS310_POLL_TIMEOUT_US(rate);

	/* Poll for sensor readiness; base the timeout upon the sample rate. */
	rc = regmap_read_poll_timeout(data->regmap, DPS310_MEAS_CFG, ready,
				      ready & DPS310_PRS_RDY,
				      DPS310_POLL_SLEEP_US(timeout), timeout);
	if (rc)
		goto done;

	rc = regmap_bulk_read(data->regmap, DPS310_PRS_BASE, val, sizeof(val));
	if (rc < 0)
		goto done;

	raw = (val[0] << 16) | (val[1] << 8) | val[2];
	data->pressure_raw = sign_extend32(raw, 23);

done:
	mutex_unlock(&data->lock);
	return rc;
}