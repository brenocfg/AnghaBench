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
struct pm860x_battery_info {scalar_t__ temp_type; int present; int start_soc; char* last_capacity; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BAT_WU_LOG ; 
 int CC6_BAT_DET_GPADC1 ; 
 int CCNT_AVG_SEL ; 
 int GPBIAS2_GPADC1_SET ; 
 int GPMISC1_GPADC_EN ; 
 int MEAS1_GP1 ; 
 int MEAS1_TINT ; 
 int MEAS3_BAT_DET ; 
 int MEAS3_CC ; 
 int MEAS3_IBAT ; 
 int /*<<< orphan*/  OCV_MODE_ACTIVE ; 
 int /*<<< orphan*/  PM8607_CCNT ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL6 ; 
 int /*<<< orphan*/  PM8607_GPADC_MISC1 ; 
 int /*<<< orphan*/  PM8607_GP_BIAS2 ; 
 int /*<<< orphan*/  PM8607_MEAS_EN1 ; 
 int /*<<< orphan*/  PM8607_MEAS_EN3 ; 
 int /*<<< orphan*/  PM8607_MEAS_OFF_TIME1 ; 
 int /*<<< orphan*/  PM8607_MEAS_OFF_TIME2 ; 
 int /*<<< orphan*/  PM8607_POWER_UP_LOG ; 
 int /*<<< orphan*/  PM8607_RTC1 ; 
 int /*<<< orphan*/  PM8607_RTC_MISC2 ; 
 int /*<<< orphan*/  PM8607_STATUS_2 ; 
 scalar_t__ PM860X_TEMP_TBAT ; 
 scalar_t__ PM860X_TEMP_TINT ; 
 int STATUS2_BAT ; 
 int /*<<< orphan*/  calc_soc (struct pm860x_battery_info*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* pm860x_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm860x_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void pm860x_init_battery(struct pm860x_battery_info *info)
{
	unsigned char buf[2];
	int ret;
	int data;
	int bat_remove;
	int soc;

	/* measure enable on GPADC1 */
	data = MEAS1_GP1;
	if (info->temp_type == PM860X_TEMP_TINT)
		data |= MEAS1_TINT;
	ret = pm860x_set_bits(info->i2c, PM8607_MEAS_EN1, data, data);
	if (ret)
		goto out;

	/* measure enable on IBAT, BAT_DET, CC. IBAT is depend on CC. */
	data = MEAS3_IBAT | MEAS3_BAT_DET | MEAS3_CC;
	ret = pm860x_set_bits(info->i2c, PM8607_MEAS_EN3, data, data);
	if (ret)
		goto out;

	/* measure disable CC in sleep time  */
	ret = pm860x_reg_write(info->i2c, PM8607_MEAS_OFF_TIME1, 0x82);
	if (ret)
		goto out;
	ret = pm860x_reg_write(info->i2c, PM8607_MEAS_OFF_TIME2, 0x6c);
	if (ret)
		goto out;

	/* enable GPADC */
	ret = pm860x_set_bits(info->i2c, PM8607_GPADC_MISC1,
			    GPMISC1_GPADC_EN, GPMISC1_GPADC_EN);
	if (ret < 0)
		goto out;

	/* detect battery via GPADC1 */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL6,
			    CC6_BAT_DET_GPADC1, CC6_BAT_DET_GPADC1);
	if (ret < 0)
		goto out;

	ret = pm860x_set_bits(info->i2c, PM8607_CCNT, 7 << 3,
			      CCNT_AVG_SEL);
	if (ret < 0)
		goto out;

	/* set GPADC1 bias */
	ret = pm860x_set_bits(info->i2c, PM8607_GP_BIAS2, 0xF << 4,
			      GPBIAS2_GPADC1_SET);
	if (ret < 0)
		goto out;

	/* check whether battery present) */
	mutex_lock(&info->lock);
	ret = pm860x_reg_read(info->i2c, PM8607_STATUS_2);
	if (ret < 0) {
		mutex_unlock(&info->lock);
		goto out;
	}
	if (ret & STATUS2_BAT) {
		info->present = 1;
		info->temp_type = PM860X_TEMP_TBAT;
	} else {
		info->present = 0;
		info->temp_type = PM860X_TEMP_TINT;
	}
	mutex_unlock(&info->lock);

	calc_soc(info, OCV_MODE_ACTIVE, &soc);

	data = pm860x_reg_read(info->i2c, PM8607_POWER_UP_LOG);
	bat_remove = data & BAT_WU_LOG;

	dev_dbg(info->dev, "battery wake up? %s\n",
		bat_remove != 0 ? "yes" : "no");

	/* restore SOC from RTC domain register */
	if (bat_remove == 0) {
		buf[0] = pm860x_reg_read(info->i2c, PM8607_RTC_MISC2);
		buf[1] = pm860x_reg_read(info->i2c, PM8607_RTC1);
		data = ((buf[1] & 0x3) << 5) | ((buf[0] >> 3) & 0x1F);
		if (data > soc + 15)
			info->start_soc = soc;
		else if (data < soc - 15)
			info->start_soc = soc;
		else
			info->start_soc = data;
		dev_dbg(info->dev, "soc_rtc %d, soc_ocv :%d\n", data, soc);
	} else {
		pm860x_set_bits(info->i2c, PM8607_POWER_UP_LOG,
				BAT_WU_LOG, BAT_WU_LOG);
		info->start_soc = soc;
	}
	info->last_capacity = info->start_soc;
	dev_dbg(info->dev, "init soc : %d\n", info->last_capacity);
out:
	return;
}