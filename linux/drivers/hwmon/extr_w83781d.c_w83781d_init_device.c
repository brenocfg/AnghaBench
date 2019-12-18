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
struct w83781d_data {int type; int* sens; int* fan_min; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  vrm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int* BIT_SCFG1 ; 
 int* BIT_SCFG2 ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_CONFIG ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS2 ; 
 int /*<<< orphan*/  W83781D_REG_CONFIG ; 
 int /*<<< orphan*/  W83781D_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  W83781D_REG_PWMCLK12 ; 
 int /*<<< orphan*/  W83781D_REG_SCFG1 ; 
 int /*<<< orphan*/  W83781D_REG_SCFG2 ; 
 int /*<<< orphan*/  W83781D_REG_TEMP2_CONFIG ; 
 int /*<<< orphan*/  W83781D_REG_TEMP3_CONFIG ; 
 int as99127f ; 
 struct w83781d_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ init ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ reset ; 
 int /*<<< orphan*/  vid_which_vrm () ; 
 int w83781d ; 
 int w83781d_read_value (struct w83781d_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83781d_write_value (struct w83781d_data*,int /*<<< orphan*/ ,int) ; 
 int w83783s ; 

__attribute__((used)) static void
w83781d_init_device(struct device *dev)
{
	struct w83781d_data *data = dev_get_drvdata(dev);
	int i, p;
	int type = data->type;
	u8 tmp;

	if (reset && type != as99127f) { /*
					  * this resets registers we don't have
					  * documentation for on the as99127f
					  */
		/*
		 * Resetting the chip has been the default for a long time,
		 * but it causes the BIOS initializations (fan clock dividers,
		 * thermal sensor types...) to be lost, so it is now optional.
		 * It might even go away if nobody reports it as being useful,
		 * as I see very little reason why this would be needed at
		 * all.
		 */
		dev_info(dev,
			 "If reset=1 solved a problem you were having, please report!\n");

		/* save these registers */
		i = w83781d_read_value(data, W83781D_REG_BEEP_CONFIG);
		p = w83781d_read_value(data, W83781D_REG_PWMCLK12);
		/*
		 * Reset all except Watchdog values and last conversion values
		 * This sets fan-divs to 2, among others
		 */
		w83781d_write_value(data, W83781D_REG_CONFIG, 0x80);
		/*
		 * Restore the registers and disable power-on abnormal beep.
		 * This saves FAN 1/2/3 input/output values set by BIOS.
		 */
		w83781d_write_value(data, W83781D_REG_BEEP_CONFIG, i | 0x80);
		w83781d_write_value(data, W83781D_REG_PWMCLK12, p);
		/*
		 * Disable master beep-enable (reset turns it on).
		 * Individual beep_mask should be reset to off but for some
		 * reason disabling this bit helps some people not get beeped
		 */
		w83781d_write_value(data, W83781D_REG_BEEP_INTS2, 0);
	}

	/*
	 * Disable power-on abnormal beep, as advised by the datasheet.
	 * Already done if reset=1.
	 */
	if (init && !reset && type != as99127f) {
		i = w83781d_read_value(data, W83781D_REG_BEEP_CONFIG);
		w83781d_write_value(data, W83781D_REG_BEEP_CONFIG, i | 0x80);
	}

	data->vrm = vid_which_vrm();

	if ((type != w83781d) && (type != as99127f)) {
		tmp = w83781d_read_value(data, W83781D_REG_SCFG1);
		for (i = 1; i <= 3; i++) {
			if (!(tmp & BIT_SCFG1[i - 1])) {
				data->sens[i - 1] = 4;
			} else {
				if (w83781d_read_value
				    (data,
				     W83781D_REG_SCFG2) & BIT_SCFG2[i - 1])
					data->sens[i - 1] = 1;
				else
					data->sens[i - 1] = 2;
			}
			if (type == w83783s && i == 2)
				break;
		}
	}

	if (init && type != as99127f) {
		/* Enable temp2 */
		tmp = w83781d_read_value(data, W83781D_REG_TEMP2_CONFIG);
		if (tmp & 0x01) {
			dev_warn(dev,
				 "Enabling temp2, readings might not make sense\n");
			w83781d_write_value(data, W83781D_REG_TEMP2_CONFIG,
				tmp & 0xfe);
		}

		/* Enable temp3 */
		if (type != w83783s) {
			tmp = w83781d_read_value(data,
				W83781D_REG_TEMP3_CONFIG);
			if (tmp & 0x01) {
				dev_warn(dev,
					 "Enabling temp3, readings might not make sense\n");
				w83781d_write_value(data,
					W83781D_REG_TEMP3_CONFIG, tmp & 0xfe);
			}
		}
	}

	/* Start monitoring */
	w83781d_write_value(data, W83781D_REG_CONFIG,
			    (w83781d_read_value(data,
						W83781D_REG_CONFIG) & 0xf7)
			    | 0x01);

	/* A few vars need to be filled upon startup */
	for (i = 0; i < 3; i++) {
		data->fan_min[i] = w83781d_read_value(data,
					W83781D_REG_FAN_MIN(i));
	}

	mutex_init(&data->update_lock);
}