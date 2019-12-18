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
typedef  int u8 ;
struct dme1737_data {int valid; int has_features; int vid; int* in; int* in_min; int* in_max; int* temp; int* temp_min; int* temp_max; int* temp_offset; int* fan; int* fan_min; int* fan_opt; int* fan_max; int* pwm; int* pwm_freq; int* pwm_config; int* pwm_min; int* pwm_rr; int* zone_low; scalar_t__ type; int* zone_abs; int* zone_hyst; int alarms; int /*<<< orphan*/  update_lock; void* last_update; int /*<<< orphan*/  client; void* last_vbat; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ DME1737_REG_ALARM1 ; 
 scalar_t__ DME1737_REG_ALARM2 ; 
 scalar_t__ DME1737_REG_ALARM3 ; 
 scalar_t__ DME1737_REG_CONFIG ; 
 scalar_t__ DME1737_REG_FAN (int) ; 
 scalar_t__ DME1737_REG_FAN_MAX (int) ; 
 scalar_t__ DME1737_REG_FAN_MIN (int) ; 
 scalar_t__ DME1737_REG_FAN_OPT (int) ; 
 scalar_t__ DME1737_REG_IN (int) ; 
 size_t* DME1737_REG_IN_LSB ; 
 int* DME1737_REG_IN_LSB_SHL ; 
 scalar_t__ DME1737_REG_IN_MAX (int) ; 
 scalar_t__ DME1737_REG_IN_MIN (int) ; 
 scalar_t__ DME1737_REG_IN_TEMP_LSB (int) ; 
 scalar_t__ DME1737_REG_PWM (int) ; 
 scalar_t__ DME1737_REG_PWM_CONFIG (int) ; 
 scalar_t__ DME1737_REG_PWM_FREQ (int) ; 
 scalar_t__ DME1737_REG_PWM_MIN (int) ; 
 scalar_t__ DME1737_REG_PWM_RR (int) ; 
 scalar_t__ DME1737_REG_TEMP (int) ; 
 size_t* DME1737_REG_TEMP_LSB ; 
 int* DME1737_REG_TEMP_LSB_SHL ; 
 scalar_t__ DME1737_REG_TEMP_MAX (int) ; 
 scalar_t__ DME1737_REG_TEMP_MIN (int) ; 
 scalar_t__ DME1737_REG_TEMP_OFFSET (int) ; 
 scalar_t__ DME1737_REG_VID ; 
 scalar_t__ DME1737_REG_ZONE_ABS (int) ; 
 scalar_t__ DME1737_REG_ZONE_HYST (int) ; 
 scalar_t__ DME1737_REG_ZONE_LOW (int) ; 
 int HAS_FAN (int) ; 
 int HAS_IN7 ; 
 int HAS_PWM (int) ; 
 int HAS_TEMP_OFFSET ; 
 int HAS_VID ; 
 int HAS_ZONE3 ; 
 int HAS_ZONE_HYST ; 
 int HZ ; 
 struct dme1737_data* dev_get_drvdata (struct device*) ; 
 int dme1737_read (struct dme1737_data*,scalar_t__) ; 
 int /*<<< orphan*/  dme1737_write (struct dme1737_data*,scalar_t__,int) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sch5127 ; 
 scalar_t__ time_after (void*,void*) ; 

__attribute__((used)) static struct dme1737_data *dme1737_update_device(struct device *dev)
{
	struct dme1737_data *data = dev_get_drvdata(dev);
	int ix;
	u8 lsb[6];

	mutex_lock(&data->update_lock);

	/* Enable a Vbat monitoring cycle every 10 mins */
	if (time_after(jiffies, data->last_vbat + 600 * HZ) || !data->valid) {
		dme1737_write(data, DME1737_REG_CONFIG, dme1737_read(data,
						DME1737_REG_CONFIG) | 0x10);
		data->last_vbat = jiffies;
	}

	/* Sample register contents every 1 sec */
	if (time_after(jiffies, data->last_update + HZ) || !data->valid) {
		if (data->has_features & HAS_VID) {
			data->vid = dme1737_read(data, DME1737_REG_VID) &
				0x3f;
		}

		/* In (voltage) registers */
		for (ix = 0; ix < ARRAY_SIZE(data->in); ix++) {
			/*
			 * Voltage inputs are stored as 16 bit values even
			 * though they have only 12 bits resolution. This is
			 * to make it consistent with the temp inputs.
			 */
			if (ix == 7 && !(data->has_features & HAS_IN7))
				continue;
			data->in[ix] = dme1737_read(data,
					DME1737_REG_IN(ix)) << 8;
			data->in_min[ix] = dme1737_read(data,
					DME1737_REG_IN_MIN(ix));
			data->in_max[ix] = dme1737_read(data,
					DME1737_REG_IN_MAX(ix));
		}

		/* Temp registers */
		for (ix = 0; ix < ARRAY_SIZE(data->temp); ix++) {
			/*
			 * Temp inputs are stored as 16 bit values even
			 * though they have only 12 bits resolution. This is
			 * to take advantage of implicit conversions between
			 * register values (2's complement) and temp values
			 * (signed decimal).
			 */
			data->temp[ix] = dme1737_read(data,
					DME1737_REG_TEMP(ix)) << 8;
			data->temp_min[ix] = dme1737_read(data,
					DME1737_REG_TEMP_MIN(ix));
			data->temp_max[ix] = dme1737_read(data,
					DME1737_REG_TEMP_MAX(ix));
			if (data->has_features & HAS_TEMP_OFFSET) {
				data->temp_offset[ix] = dme1737_read(data,
						DME1737_REG_TEMP_OFFSET(ix));
			}
		}

		/*
		 * In and temp LSB registers
		 * The LSBs are latched when the MSBs are read, so the order in
		 * which the registers are read (MSB first, then LSB) is
		 * important!
		 */
		for (ix = 0; ix < ARRAY_SIZE(lsb); ix++) {
			if (ix == 5 && !(data->has_features & HAS_IN7))
				continue;
			lsb[ix] = dme1737_read(data,
					DME1737_REG_IN_TEMP_LSB(ix));
		}
		for (ix = 0; ix < ARRAY_SIZE(data->in); ix++) {
			if (ix == 7 && !(data->has_features & HAS_IN7))
				continue;
			data->in[ix] |= (lsb[DME1737_REG_IN_LSB[ix]] <<
					DME1737_REG_IN_LSB_SHL[ix]) & 0xf0;
		}
		for (ix = 0; ix < ARRAY_SIZE(data->temp); ix++) {
			data->temp[ix] |= (lsb[DME1737_REG_TEMP_LSB[ix]] <<
					DME1737_REG_TEMP_LSB_SHL[ix]) & 0xf0;
		}

		/* Fan registers */
		for (ix = 0; ix < ARRAY_SIZE(data->fan); ix++) {
			/*
			 * Skip reading registers if optional fans are not
			 * present
			 */
			if (!(data->has_features & HAS_FAN(ix)))
				continue;
			data->fan[ix] = dme1737_read(data,
					DME1737_REG_FAN(ix));
			data->fan[ix] |= dme1737_read(data,
					DME1737_REG_FAN(ix) + 1) << 8;
			data->fan_min[ix] = dme1737_read(data,
					DME1737_REG_FAN_MIN(ix));
			data->fan_min[ix] |= dme1737_read(data,
					DME1737_REG_FAN_MIN(ix) + 1) << 8;
			data->fan_opt[ix] = dme1737_read(data,
					DME1737_REG_FAN_OPT(ix));
			/* fan_max exists only for fan[5-6] */
			if (ix > 3) {
				data->fan_max[ix - 4] = dme1737_read(data,
					DME1737_REG_FAN_MAX(ix));
			}
		}

		/* PWM registers */
		for (ix = 0; ix < ARRAY_SIZE(data->pwm); ix++) {
			/*
			 * Skip reading registers if optional PWMs are not
			 * present
			 */
			if (!(data->has_features & HAS_PWM(ix)))
				continue;
			data->pwm[ix] = dme1737_read(data,
					DME1737_REG_PWM(ix));
			data->pwm_freq[ix] = dme1737_read(data,
					DME1737_REG_PWM_FREQ(ix));
			/* pwm_config and pwm_min exist only for pwm[1-3] */
			if (ix < 3) {
				data->pwm_config[ix] = dme1737_read(data,
						DME1737_REG_PWM_CONFIG(ix));
				data->pwm_min[ix] = dme1737_read(data,
						DME1737_REG_PWM_MIN(ix));
			}
		}
		for (ix = 0; ix < ARRAY_SIZE(data->pwm_rr); ix++) {
			data->pwm_rr[ix] = dme1737_read(data,
						DME1737_REG_PWM_RR(ix));
		}

		/* Thermal zone registers */
		for (ix = 0; ix < ARRAY_SIZE(data->zone_low); ix++) {
			/* Skip reading registers if zone3 is not present */
			if ((ix == 2) && !(data->has_features & HAS_ZONE3))
				continue;
			/* sch5127 zone2 registers are special */
			if ((ix == 1) && (data->type == sch5127)) {
				data->zone_low[1] = dme1737_read(data,
						DME1737_REG_ZONE_LOW(2));
				data->zone_abs[1] = dme1737_read(data,
						DME1737_REG_ZONE_ABS(2));
			} else {
				data->zone_low[ix] = dme1737_read(data,
						DME1737_REG_ZONE_LOW(ix));
				data->zone_abs[ix] = dme1737_read(data,
						DME1737_REG_ZONE_ABS(ix));
			}
		}
		if (data->has_features & HAS_ZONE_HYST) {
			for (ix = 0; ix < ARRAY_SIZE(data->zone_hyst); ix++) {
				data->zone_hyst[ix] = dme1737_read(data,
						DME1737_REG_ZONE_HYST(ix));
			}
		}

		/* Alarm registers */
		data->alarms = dme1737_read(data,
						DME1737_REG_ALARM1);
		/*
		 * Bit 7 tells us if the other alarm registers are non-zero and
		 * therefore also need to be read
		 */
		if (data->alarms & 0x80) {
			data->alarms |= dme1737_read(data,
						DME1737_REG_ALARM2) << 8;
			data->alarms |= dme1737_read(data,
						DME1737_REG_ALARM3) << 16;
		}

		/*
		 * The ISA chips require explicit clearing of alarm bits.
		 * Don't worry, an alarm will come back if the condition
		 * that causes it still exists
		 */
		if (!data->client) {
			if (data->alarms & 0xff0000)
				dme1737_write(data, DME1737_REG_ALARM3, 0xff);
			if (data->alarms & 0xff00)
				dme1737_write(data, DME1737_REG_ALARM2, 0xff);
			if (data->alarms & 0xff)
				dme1737_write(data, DME1737_REG_ALARM1, 0xff);
		}

		data->last_update = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}