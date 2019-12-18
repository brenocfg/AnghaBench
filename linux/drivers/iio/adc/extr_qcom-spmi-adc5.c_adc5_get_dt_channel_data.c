#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct device_node {char* name; } ;
struct device {int dummy; } ;
struct adc5_data {int /*<<< orphan*/  hw_settle_1; int /*<<< orphan*/  hw_settle_2; int /*<<< orphan*/  decimation; TYPE_1__* adc_chans; } ;
struct adc5_chip {TYPE_3__* data; struct device* dev; } ;
struct adc5_channel_prop {size_t channel; char const* datasheet_name; int decimation; int prescale; int hw_settle_time; int avg_samples; int /*<<< orphan*/  cal_val; int /*<<< orphan*/  cal_method; } ;
typedef  int /*<<< orphan*/  dig_version ;
struct TYPE_6__ {TYPE_2__* adc_chans; } ;
struct TYPE_5__ {int prescale_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  datasheet_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC5_ABSOLUTE_CAL ; 
 int ADC5_DECIMATION_DEFAULT ; 
 scalar_t__ ADC5_HW_SETTLE_DIFF_MAJOR ; 
 scalar_t__ ADC5_HW_SETTLE_DIFF_MINOR ; 
 size_t ADC5_PARALLEL_ISENSE_VBAT_IDATA ; 
 int /*<<< orphan*/  ADC5_RATIOMETRIC_CAL ; 
 int /*<<< orphan*/  ADC5_TIMER_CAL ; 
 int /*<<< orphan*/  ADC5_USR_REVISION1 ; 
 int EINVAL ; 
 int VADC_DEF_AVG_SAMPLES ; 
 int VADC_DEF_HW_SETTLE_TIME ; 
 int adc5_avg_samples_from_dt (size_t) ; 
 int adc5_decimation_from_dt (size_t,int /*<<< orphan*/ ) ; 
 int adc5_hw_settle_time_from_dt (size_t,int /*<<< orphan*/ ) ; 
 int adc5_prescaling_from_dt (size_t,size_t) ; 
 int adc5_read (struct adc5_chip*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,size_t,char const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,size_t*) ; 
 int of_property_read_u32_array (struct device_node*,char*,size_t*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int adc5_get_dt_channel_data(struct adc5_chip *adc,
				    struct adc5_channel_prop *prop,
				    struct device_node *node,
				    const struct adc5_data *data)
{
	const char *name = node->name, *channel_name;
	u32 chan, value, varr[2];
	int ret;
	struct device *dev = adc->dev;

	ret = of_property_read_u32(node, "reg", &chan);
	if (ret) {
		dev_err(dev, "invalid channel number %s\n", name);
		return ret;
	}

	if (chan > ADC5_PARALLEL_ISENSE_VBAT_IDATA ||
	    !data->adc_chans[chan].datasheet_name) {
		dev_err(dev, "%s invalid channel number %d\n", name, chan);
		return -EINVAL;
	}

	/* the channel has DT description */
	prop->channel = chan;

	channel_name = of_get_property(node,
				"label", NULL) ? : node->name;
	if (!channel_name) {
		pr_err("Invalid channel name\n");
		return -EINVAL;
	}
	prop->datasheet_name = channel_name;

	ret = of_property_read_u32(node, "qcom,decimation", &value);
	if (!ret) {
		ret = adc5_decimation_from_dt(value, data->decimation);
		if (ret < 0) {
			dev_err(dev, "%02x invalid decimation %d\n",
				chan, value);
			return ret;
		}
		prop->decimation = ret;
	} else {
		prop->decimation = ADC5_DECIMATION_DEFAULT;
	}

	ret = of_property_read_u32_array(node, "qcom,pre-scaling", varr, 2);
	if (!ret) {
		ret = adc5_prescaling_from_dt(varr[0], varr[1]);
		if (ret < 0) {
			dev_err(dev, "%02x invalid pre-scaling <%d %d>\n",
				chan, varr[0], varr[1]);
			return ret;
		}
		prop->prescale = ret;
	} else {
		prop->prescale =
			adc->data->adc_chans[prop->channel].prescale_index;
	}

	ret = of_property_read_u32(node, "qcom,hw-settle-time", &value);
	if (!ret) {
		u8 dig_version[2];

		ret = adc5_read(adc, ADC5_USR_REVISION1, dig_version,
							sizeof(dig_version));
		if (ret < 0) {
			dev_err(dev, "Invalid dig version read %d\n", ret);
			return ret;
		}

		pr_debug("dig_ver:minor:%d, major:%d\n", dig_version[0],
						dig_version[1]);
		/* Digital controller >= 5.3 have hw_settle_2 option */
		if (dig_version[0] >= ADC5_HW_SETTLE_DIFF_MINOR &&
			dig_version[1] >= ADC5_HW_SETTLE_DIFF_MAJOR)
			ret = adc5_hw_settle_time_from_dt(value,
							data->hw_settle_2);
		else
			ret = adc5_hw_settle_time_from_dt(value,
							data->hw_settle_1);

		if (ret < 0) {
			dev_err(dev, "%02x invalid hw-settle-time %d us\n",
				chan, value);
			return ret;
		}
		prop->hw_settle_time = ret;
	} else {
		prop->hw_settle_time = VADC_DEF_HW_SETTLE_TIME;
	}

	ret = of_property_read_u32(node, "qcom,avg-samples", &value);
	if (!ret) {
		ret = adc5_avg_samples_from_dt(value);
		if (ret < 0) {
			dev_err(dev, "%02x invalid avg-samples %d\n",
				chan, value);
			return ret;
		}
		prop->avg_samples = ret;
	} else {
		prop->avg_samples = VADC_DEF_AVG_SAMPLES;
	}

	if (of_property_read_bool(node, "qcom,ratiometric"))
		prop->cal_method = ADC5_RATIOMETRIC_CAL;
	else
		prop->cal_method = ADC5_ABSOLUTE_CAL;

	/*
	 * Default to using timer calibration. Using a fresh calibration value
	 * for every conversion will increase the overall time for a request.
	 */
	prop->cal_val = ADC5_TIMER_CAL;

	dev_dbg(dev, "%02x name %s\n", chan, name);

	return 0;
}