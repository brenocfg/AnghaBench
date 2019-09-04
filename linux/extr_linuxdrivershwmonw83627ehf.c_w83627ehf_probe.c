#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_21__ ;
typedef  struct TYPE_33__   TYPE_20__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
struct w83627ehf_sio_data {size_t kind; int /*<<< orphan*/  sioreg; } ;
struct w83627ehf_data {int bank; int in_num; int pwm_num; int have_temp; int* reg_temp_config; int* temp_src; int in6_skip; int have_temp_offset; int temp3_val_only; int has_fan_div; int* REG_FAN_STEP_OUTPUT; int vrm; int vid; int has_fan; int has_fan_min; int /*<<< orphan*/  hwmon_dev; scalar_t__* reg_temp_hyst; scalar_t__* reg_temp_over; void* temp_label; int /*<<< orphan*/ * pwm_enable; int /*<<< orphan*/ * pwm_enable_orig; int /*<<< orphan*/  name; int /*<<< orphan*/  scale_in; int /*<<< orphan*/  REG_FAN_MAX_OUTPUT; void* REG_FAN_STOP_TIME; void* REG_FAN_STOP_OUTPUT; void* REG_FAN_START_OUTPUT; void* REG_FAN_MIN; void* REG_FAN; void* REG_TARGET; void* REG_PWM; void* fan_from_reg_min; void* fan_from_reg; int /*<<< orphan*/ * reg_temp; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  lock; scalar_t__ addr; } ;
struct sensor_device_attribute {size_t index; int /*<<< orphan*/  dev_attr; } ;
struct resource {scalar_t__ start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_42__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_41__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_40__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_39__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_38__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_37__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_36__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_35__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_34__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_33__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_32__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_31__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_30__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_29__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_28__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_27__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_26__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_25__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_24__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_23__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_22__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sensor_device_attribute*) ; 
 int /*<<< orphan*/  DRVNAME ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IOREGION_LENGTH ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 void* NCT6775_REG_FAN ; 
 int NCT6775_REG_FAN_DEBOUNCE ; 
 int /*<<< orphan*/  NCT6775_REG_FAN_MAX_OUTPUT ; 
 void* NCT6775_REG_FAN_START_OUTPUT ; 
 int* NCT6775_REG_FAN_STEP_OUTPUT ; 
 void* NCT6775_REG_FAN_STOP_OUTPUT ; 
 void* NCT6775_REG_FAN_STOP_TIME ; 
 void* NCT6775_REG_PWM ; 
 void* NCT6775_REG_TARGET ; 
 int /*<<< orphan*/ * NCT6775_REG_TEMP ; 
 int* NCT6775_REG_TEMP_CONFIG ; 
 scalar_t__* NCT6775_REG_TEMP_HYST ; 
 scalar_t__* NCT6775_REG_TEMP_OVER ; 
 int* NCT6775_REG_TEMP_SOURCE ; 
 void* NCT6776_REG_FAN_MIN ; 
 int NUM_REG_TEMP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SIO_REG_EN_VRM10 ; 
 int SIO_REG_VID_CTRL ; 
 int SIO_REG_VID_DATA ; 
 int /*<<< orphan*/  W83627EHF_LD_HWM ; 
 void* W83627EHF_REG_FAN ; 
 int /*<<< orphan*/  W83627EHF_REG_FAN_MAX_OUTPUT_COMMON ; 
 int /*<<< orphan*/  W83627EHF_REG_FAN_MAX_OUTPUT_W83667_B ; 
 void* W83627EHF_REG_FAN_MIN ; 
 void* W83627EHF_REG_FAN_START_OUTPUT ; 
 int* W83627EHF_REG_FAN_STEP_OUTPUT_COMMON ; 
 int* W83627EHF_REG_FAN_STEP_OUTPUT_W83667_B ; 
 void* W83627EHF_REG_FAN_STOP_OUTPUT ; 
 void* W83627EHF_REG_FAN_STOP_TIME ; 
 void* W83627EHF_REG_PWM ; 
 void* W83627EHF_REG_TARGET ; 
 int* W83627EHF_REG_TEMP_CONFIG ; 
 int /*<<< orphan*/  W83667HG_LD_VID ; 
 int /*<<< orphan*/  dev_attr_cpu0_vid ; 
 int /*<<< orphan*/  dev_attr_name ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long,scalar_t__) ; 
 struct w83627ehf_sio_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 struct w83627ehf_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fan_debounce ; 
 void* fan_from_reg13 ; 
 void* fan_from_reg16 ; 
 void* fan_from_reg8 ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
#define  nct6775 132 
 void* nct6775_temp_label ; 
#define  nct6776 131 
 void* nct6776_temp_label ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct w83627ehf_data*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  request_region (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_in_common ; 
 int /*<<< orphan*/  scale_in_w83627uhg ; 
 TYPE_21__* sda_caseopen ; 
 TYPE_20__* sda_fan_alarm ; 
 TYPE_19__* sda_fan_div ; 
 TYPE_18__* sda_fan_input ; 
 TYPE_17__* sda_fan_min ; 
 TYPE_16__* sda_in_alarm ; 
 TYPE_15__* sda_in_input ; 
 TYPE_14__* sda_in_max ; 
 TYPE_13__* sda_in_min ; 
 TYPE_12__* sda_pwm ; 
 TYPE_11__* sda_pwm_enable ; 
 TYPE_10__* sda_pwm_mode ; 
 struct sensor_device_attribute* sda_sf3_arrays ; 
 struct sensor_device_attribute* sda_sf3_arrays_fan3 ; 
 struct sensor_device_attribute* sda_sf3_arrays_fan4 ; 
 struct sensor_device_attribute* sda_sf3_max_step_arrays ; 
 TYPE_9__* sda_target_temp ; 
 TYPE_8__* sda_temp_alarm ; 
 TYPE_7__* sda_temp_input ; 
 TYPE_6__* sda_temp_label ; 
 TYPE_5__* sda_temp_max ; 
 TYPE_4__* sda_temp_max_hyst ; 
 TYPE_3__* sda_temp_offset ; 
 TYPE_2__* sda_temp_type ; 
 TYPE_1__* sda_tolerance ; 
 int superio_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_exit (int /*<<< orphan*/ ) ; 
 int superio_inb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  superio_outb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vid_which_vrm () ; 
 int /*<<< orphan*/  w82627ehf_swap_tempreg (struct w83627ehf_data*,int,int) ; 
 size_t w83627ehf ; 
 int /*<<< orphan*/  w83627ehf_check_fan_inputs (struct w83627ehf_sio_data*,struct w83627ehf_data*) ; 
 int /*<<< orphan*/ * w83627ehf_device_names ; 
 int /*<<< orphan*/  w83627ehf_device_remove_files (struct device*) ; 
 int /*<<< orphan*/  w83627ehf_init_device (struct w83627ehf_data*,int const) ; 
 int w83627ehf_read_value (struct w83627ehf_data*,int) ; 
 int /*<<< orphan*/  w83627ehf_set_temp_reg_ehf (struct w83627ehf_data*,int) ; 
 int /*<<< orphan*/  w83627ehf_update_fan_div_common (struct device*,struct w83627ehf_data*) ; 
 int /*<<< orphan*/  w83627ehf_update_pwm_common (struct device*,struct w83627ehf_data*) ; 
#define  w83627uhg 130 
#define  w83667hg 129 
#define  w83667hg_b 128 
 void* w83667hg_b_temp_label ; 

__attribute__((used)) static int w83627ehf_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct w83627ehf_sio_data *sio_data = dev_get_platdata(dev);
	struct w83627ehf_data *data;
	struct resource *res;
	u8 en_vrm10;
	int i, err = 0;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!request_region(res->start, IOREGION_LENGTH, DRVNAME)) {
		err = -EBUSY;
		dev_err(dev, "Failed to request region 0x%lx-0x%lx\n",
			(unsigned long)res->start,
			(unsigned long)res->start + IOREGION_LENGTH - 1);
		goto exit;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(struct w83627ehf_data),
			    GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit_release;
	}

	data->addr = res->start;
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);
	data->name = w83627ehf_device_names[sio_data->kind];
	data->bank = 0xff;		/* Force initial bank selection */
	platform_set_drvdata(pdev, data);

	/* 627EHG and 627EHF have 10 voltage inputs; 627DHG and 667HG have 9 */
	data->in_num = (sio_data->kind == w83627ehf) ? 10 : 9;
	/* 667HG, NCT6775F, and NCT6776F have 3 pwms, and 627UHG has only 2 */
	switch (sio_data->kind) {
	default:
		data->pwm_num = 4;
		break;
	case w83667hg:
	case w83667hg_b:
	case nct6775:
	case nct6776:
		data->pwm_num = 3;
		break;
	case w83627uhg:
		data->pwm_num = 2;
		break;
	}

	/* Default to 3 temperature inputs, code below will adjust as needed */
	data->have_temp = 0x07;

	/* Deal with temperature register setup first. */
	if (sio_data->kind == nct6775 || sio_data->kind == nct6776) {
		int mask = 0;

		/*
		 * Display temperature sensor output only if it monitors
		 * a source other than one already reported. Always display
		 * first three temperature registers, though.
		 */
		for (i = 0; i < NUM_REG_TEMP; i++) {
			u8 src;

			data->reg_temp[i] = NCT6775_REG_TEMP[i];
			data->reg_temp_over[i] = NCT6775_REG_TEMP_OVER[i];
			data->reg_temp_hyst[i] = NCT6775_REG_TEMP_HYST[i];
			data->reg_temp_config[i] = NCT6775_REG_TEMP_CONFIG[i];

			src = w83627ehf_read_value(data,
						   NCT6775_REG_TEMP_SOURCE[i]);
			src &= 0x1f;
			if (src && !(mask & (1 << src))) {
				data->have_temp |= 1 << i;
				mask |= 1 << src;
			}

			data->temp_src[i] = src;

			/*
			 * Now do some register swapping if index 0..2 don't
			 * point to SYSTIN(1), CPUIN(2), and AUXIN(3).
			 * Idea is to have the first three attributes
			 * report SYSTIN, CPUIN, and AUXIN if possible
			 * without overriding the basic system configuration.
			 */
			if (i > 0 && data->temp_src[0] != 1
			    && data->temp_src[i] == 1)
				w82627ehf_swap_tempreg(data, 0, i);
			if (i > 1 && data->temp_src[1] != 2
			    && data->temp_src[i] == 2)
				w82627ehf_swap_tempreg(data, 1, i);
			if (i > 2 && data->temp_src[2] != 3
			    && data->temp_src[i] == 3)
				w82627ehf_swap_tempreg(data, 2, i);
		}
		if (sio_data->kind == nct6776) {
			/*
			 * On NCT6776, AUXTIN and VIN3 pins are shared.
			 * Only way to detect it is to check if AUXTIN is used
			 * as a temperature source, and if that source is
			 * enabled.
			 *
			 * If that is the case, disable in6, which reports VIN3.
			 * Otherwise disable temp3.
			 */
			if (data->temp_src[2] == 3) {
				u8 reg;

				if (data->reg_temp_config[2])
					reg = w83627ehf_read_value(data,
						data->reg_temp_config[2]);
				else
					reg = 0; /* Assume AUXTIN is used */

				if (reg & 0x01)
					data->have_temp &= ~(1 << 2);
				else
					data->in6_skip = 1;
			}
			data->temp_label = nct6776_temp_label;
		} else {
			data->temp_label = nct6775_temp_label;
		}
		data->have_temp_offset = data->have_temp & 0x07;
		for (i = 0; i < 3; i++) {
			if (data->temp_src[i] > 3)
				data->have_temp_offset &= ~(1 << i);
		}
	} else if (sio_data->kind == w83667hg_b) {
		u8 reg;

		w83627ehf_set_temp_reg_ehf(data, 4);

		/*
		 * Temperature sources are selected with bank 0, registers 0x49
		 * and 0x4a.
		 */
		reg = w83627ehf_read_value(data, 0x4a);
		data->temp_src[0] = reg >> 5;
		reg = w83627ehf_read_value(data, 0x49);
		data->temp_src[1] = reg & 0x07;
		data->temp_src[2] = (reg >> 4) & 0x07;

		/*
		 * W83667HG-B has another temperature register at 0x7e.
		 * The temperature source is selected with register 0x7d.
		 * Support it if the source differs from already reported
		 * sources.
		 */
		reg = w83627ehf_read_value(data, 0x7d);
		reg &= 0x07;
		if (reg != data->temp_src[0] && reg != data->temp_src[1]
		    && reg != data->temp_src[2]) {
			data->temp_src[3] = reg;
			data->have_temp |= 1 << 3;
		}

		/*
		 * Chip supports either AUXTIN or VIN3. Try to find out which
		 * one.
		 */
		reg = w83627ehf_read_value(data, W83627EHF_REG_TEMP_CONFIG[2]);
		if (data->temp_src[2] == 2 && (reg & 0x01))
			data->have_temp &= ~(1 << 2);

		if ((data->temp_src[2] == 2 && (data->have_temp & (1 << 2)))
		    || (data->temp_src[3] == 2 && (data->have_temp & (1 << 3))))
			data->in6_skip = 1;

		data->temp_label = w83667hg_b_temp_label;
		data->have_temp_offset = data->have_temp & 0x07;
		for (i = 0; i < 3; i++) {
			if (data->temp_src[i] > 2)
				data->have_temp_offset &= ~(1 << i);
		}
	} else if (sio_data->kind == w83627uhg) {
		u8 reg;

		w83627ehf_set_temp_reg_ehf(data, 3);

		/*
		 * Temperature sources for temp2 and temp3 are selected with
		 * bank 0, registers 0x49 and 0x4a.
		 */
		data->temp_src[0] = 0;	/* SYSTIN */
		reg = w83627ehf_read_value(data, 0x49) & 0x07;
		/* Adjust to have the same mapping as other source registers */
		if (reg == 0)
			data->temp_src[1] = 1;
		else if (reg >= 2 && reg <= 5)
			data->temp_src[1] = reg + 2;
		else	/* should never happen */
			data->have_temp &= ~(1 << 1);
		reg = w83627ehf_read_value(data, 0x4a);
		data->temp_src[2] = reg >> 5;

		/*
		 * Skip temp3 if source is invalid or the same as temp1
		 * or temp2.
		 */
		if (data->temp_src[2] == 2 || data->temp_src[2] == 3 ||
		    data->temp_src[2] == data->temp_src[0] ||
		    ((data->have_temp & (1 << 1)) &&
		     data->temp_src[2] == data->temp_src[1]))
			data->have_temp &= ~(1 << 2);
		else
			data->temp3_val_only = 1;	/* No limit regs */

		data->in6_skip = 1;			/* No VIN3 */

		data->temp_label = w83667hg_b_temp_label;
		data->have_temp_offset = data->have_temp & 0x03;
		for (i = 0; i < 3; i++) {
			if (data->temp_src[i] > 1)
				data->have_temp_offset &= ~(1 << i);
		}
	} else {
		w83627ehf_set_temp_reg_ehf(data, 3);

		/* Temperature sources are fixed */

		if (sio_data->kind == w83667hg) {
			u8 reg;

			/*
			 * Chip supports either AUXTIN or VIN3. Try to find
			 * out which one.
			 */
			reg = w83627ehf_read_value(data,
						W83627EHF_REG_TEMP_CONFIG[2]);
			if (reg & 0x01)
				data->have_temp &= ~(1 << 2);
			else
				data->in6_skip = 1;
		}
		data->have_temp_offset = data->have_temp & 0x07;
	}

	if (sio_data->kind == nct6775) {
		data->has_fan_div = true;
		data->fan_from_reg = fan_from_reg16;
		data->fan_from_reg_min = fan_from_reg8;
		data->REG_PWM = NCT6775_REG_PWM;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6775_REG_FAN;
		data->REG_FAN_MIN = W83627EHF_REG_FAN_MIN;
		data->REG_FAN_START_OUTPUT = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_FAN_STOP_OUTPUT = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_FAN_STOP_TIME = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_MAX_OUTPUT = NCT6775_REG_FAN_MAX_OUTPUT;
		data->REG_FAN_STEP_OUTPUT = NCT6775_REG_FAN_STEP_OUTPUT;
	} else if (sio_data->kind == nct6776) {
		data->has_fan_div = false;
		data->fan_from_reg = fan_from_reg13;
		data->fan_from_reg_min = fan_from_reg13;
		data->REG_PWM = NCT6775_REG_PWM;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6775_REG_FAN;
		data->REG_FAN_MIN = NCT6776_REG_FAN_MIN;
		data->REG_FAN_START_OUTPUT = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_FAN_STOP_OUTPUT = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_FAN_STOP_TIME = NCT6775_REG_FAN_STOP_TIME;
	} else if (sio_data->kind == w83667hg_b) {
		data->has_fan_div = true;
		data->fan_from_reg = fan_from_reg8;
		data->fan_from_reg_min = fan_from_reg8;
		data->REG_PWM = W83627EHF_REG_PWM;
		data->REG_TARGET = W83627EHF_REG_TARGET;
		data->REG_FAN = W83627EHF_REG_FAN;
		data->REG_FAN_MIN = W83627EHF_REG_FAN_MIN;
		data->REG_FAN_START_OUTPUT = W83627EHF_REG_FAN_START_OUTPUT;
		data->REG_FAN_STOP_OUTPUT = W83627EHF_REG_FAN_STOP_OUTPUT;
		data->REG_FAN_STOP_TIME = W83627EHF_REG_FAN_STOP_TIME;
		data->REG_FAN_MAX_OUTPUT =
		  W83627EHF_REG_FAN_MAX_OUTPUT_W83667_B;
		data->REG_FAN_STEP_OUTPUT =
		  W83627EHF_REG_FAN_STEP_OUTPUT_W83667_B;
	} else {
		data->has_fan_div = true;
		data->fan_from_reg = fan_from_reg8;
		data->fan_from_reg_min = fan_from_reg8;
		data->REG_PWM = W83627EHF_REG_PWM;
		data->REG_TARGET = W83627EHF_REG_TARGET;
		data->REG_FAN = W83627EHF_REG_FAN;
		data->REG_FAN_MIN = W83627EHF_REG_FAN_MIN;
		data->REG_FAN_START_OUTPUT = W83627EHF_REG_FAN_START_OUTPUT;
		data->REG_FAN_STOP_OUTPUT = W83627EHF_REG_FAN_STOP_OUTPUT;
		data->REG_FAN_STOP_TIME = W83627EHF_REG_FAN_STOP_TIME;
		data->REG_FAN_MAX_OUTPUT =
		  W83627EHF_REG_FAN_MAX_OUTPUT_COMMON;
		data->REG_FAN_STEP_OUTPUT =
		  W83627EHF_REG_FAN_STEP_OUTPUT_COMMON;
	}

	/* Setup input voltage scaling factors */
	if (sio_data->kind == w83627uhg)
		data->scale_in = scale_in_w83627uhg;
	else
		data->scale_in = scale_in_common;

	/* Initialize the chip */
	w83627ehf_init_device(data, sio_data->kind);

	data->vrm = vid_which_vrm();

	err = superio_enter(sio_data->sioreg);
	if (err)
		goto exit_release;

	/* Read VID value */
	if (sio_data->kind == w83667hg || sio_data->kind == w83667hg_b ||
	    sio_data->kind == nct6775 || sio_data->kind == nct6776) {
		/*
		 * W83667HG has different pins for VID input and output, so
		 * we can get the VID input values directly at logical device D
		 * 0xe3.
		 */
		superio_select(sio_data->sioreg, W83667HG_LD_VID);
		data->vid = superio_inb(sio_data->sioreg, 0xe3);
		err = device_create_file(dev, &dev_attr_cpu0_vid);
		if (err) {
			superio_exit(sio_data->sioreg);
			goto exit_release;
		}
	} else if (sio_data->kind != w83627uhg) {
		superio_select(sio_data->sioreg, W83627EHF_LD_HWM);
		if (superio_inb(sio_data->sioreg, SIO_REG_VID_CTRL) & 0x80) {
			/*
			 * Set VID input sensibility if needed. In theory the
			 * BIOS should have set it, but in practice it's not
			 * always the case. We only do it for the W83627EHF/EHG
			 * because the W83627DHG is more complex in this
			 * respect.
			 */
			if (sio_data->kind == w83627ehf) {
				en_vrm10 = superio_inb(sio_data->sioreg,
						       SIO_REG_EN_VRM10);
				if ((en_vrm10 & 0x08) && data->vrm == 90) {
					dev_warn(dev,
						 "Setting VID input voltage to TTL\n");
					superio_outb(sio_data->sioreg,
						     SIO_REG_EN_VRM10,
						     en_vrm10 & ~0x08);
				} else if (!(en_vrm10 & 0x08)
					   && data->vrm == 100) {
					dev_warn(dev,
						 "Setting VID input voltage to VRM10\n");
					superio_outb(sio_data->sioreg,
						     SIO_REG_EN_VRM10,
						     en_vrm10 | 0x08);
				}
			}

			data->vid = superio_inb(sio_data->sioreg,
						SIO_REG_VID_DATA);
			if (sio_data->kind == w83627ehf) /* 6 VID pins only */
				data->vid &= 0x3f;

			err = device_create_file(dev, &dev_attr_cpu0_vid);
			if (err) {
				superio_exit(sio_data->sioreg);
				goto exit_release;
			}
		} else {
			dev_info(dev,
				 "VID pins in output mode, CPU VID not available\n");
		}
	}

	if (fan_debounce &&
	    (sio_data->kind == nct6775 || sio_data->kind == nct6776)) {
		u8 tmp;

		superio_select(sio_data->sioreg, W83627EHF_LD_HWM);
		tmp = superio_inb(sio_data->sioreg, NCT6775_REG_FAN_DEBOUNCE);
		if (sio_data->kind == nct6776)
			superio_outb(sio_data->sioreg, NCT6775_REG_FAN_DEBOUNCE,
				     0x3e | tmp);
		else
			superio_outb(sio_data->sioreg, NCT6775_REG_FAN_DEBOUNCE,
				     0x1e | tmp);
		pr_info("Enabled fan debounce for chip %s\n", data->name);
	}

	w83627ehf_check_fan_inputs(sio_data, data);

	superio_exit(sio_data->sioreg);

	/* Read fan clock dividers immediately */
	w83627ehf_update_fan_div_common(dev, data);

	/* Read pwm data to save original values */
	w83627ehf_update_pwm_common(dev, data);
	for (i = 0; i < data->pwm_num; i++)
		data->pwm_enable_orig[i] = data->pwm_enable[i];

	/* Register sysfs hooks */
	for (i = 0; i < ARRAY_SIZE(sda_sf3_arrays); i++) {
		err = device_create_file(dev, &sda_sf3_arrays[i].dev_attr);
		if (err)
			goto exit_remove;
	}

	for (i = 0; i < ARRAY_SIZE(sda_sf3_max_step_arrays); i++) {
		struct sensor_device_attribute *attr =
		  &sda_sf3_max_step_arrays[i];
		if (data->REG_FAN_STEP_OUTPUT &&
		    data->REG_FAN_STEP_OUTPUT[attr->index] != 0xff) {
			err = device_create_file(dev, &attr->dev_attr);
			if (err)
				goto exit_remove;
		}
	}
	/* if fan3 and fan4 are enabled create the sf3 files for them */
	if ((data->has_fan & (1 << 2)) && data->pwm_num >= 3)
		for (i = 0; i < ARRAY_SIZE(sda_sf3_arrays_fan3); i++) {
			err = device_create_file(dev,
					&sda_sf3_arrays_fan3[i].dev_attr);
			if (err)
				goto exit_remove;
		}
	if ((data->has_fan & (1 << 3)) && data->pwm_num >= 4)
		for (i = 0; i < ARRAY_SIZE(sda_sf3_arrays_fan4); i++) {
			err = device_create_file(dev,
					&sda_sf3_arrays_fan4[i].dev_attr);
			if (err)
				goto exit_remove;
		}

	for (i = 0; i < data->in_num; i++) {
		if ((i == 6) && data->in6_skip)
			continue;
		if ((err = device_create_file(dev, &sda_in_input[i].dev_attr))
			|| (err = device_create_file(dev,
				&sda_in_alarm[i].dev_attr))
			|| (err = device_create_file(dev,
				&sda_in_min[i].dev_attr))
			|| (err = device_create_file(dev,
				&sda_in_max[i].dev_attr)))
			goto exit_remove;
	}

	for (i = 0; i < 5; i++) {
		if (data->has_fan & (1 << i)) {
			if ((err = device_create_file(dev,
					&sda_fan_input[i].dev_attr))
				|| (err = device_create_file(dev,
					&sda_fan_alarm[i].dev_attr)))
				goto exit_remove;
			if (sio_data->kind != nct6776) {
				err = device_create_file(dev,
						&sda_fan_div[i].dev_attr);
				if (err)
					goto exit_remove;
			}
			if (data->has_fan_min & (1 << i)) {
				err = device_create_file(dev,
						&sda_fan_min[i].dev_attr);
				if (err)
					goto exit_remove;
			}
			if (i < data->pwm_num &&
				((err = device_create_file(dev,
					&sda_pwm[i].dev_attr))
				|| (err = device_create_file(dev,
					&sda_pwm_mode[i].dev_attr))
				|| (err = device_create_file(dev,
					&sda_pwm_enable[i].dev_attr))
				|| (err = device_create_file(dev,
					&sda_target_temp[i].dev_attr))
				|| (err = device_create_file(dev,
					&sda_tolerance[i].dev_attr))))
				goto exit_remove;
		}
	}

	for (i = 0; i < NUM_REG_TEMP; i++) {
		if (!(data->have_temp & (1 << i)))
			continue;
		err = device_create_file(dev, &sda_temp_input[i].dev_attr);
		if (err)
			goto exit_remove;
		if (data->temp_label) {
			err = device_create_file(dev,
						 &sda_temp_label[i].dev_attr);
			if (err)
				goto exit_remove;
		}
		if (i == 2 && data->temp3_val_only)
			continue;
		if (data->reg_temp_over[i]) {
			err = device_create_file(dev,
				&sda_temp_max[i].dev_attr);
			if (err)
				goto exit_remove;
		}
		if (data->reg_temp_hyst[i]) {
			err = device_create_file(dev,
				&sda_temp_max_hyst[i].dev_attr);
			if (err)
				goto exit_remove;
		}
		if (i > 2)
			continue;
		if ((err = device_create_file(dev,
				&sda_temp_alarm[i].dev_attr))
			|| (err = device_create_file(dev,
				&sda_temp_type[i].dev_attr)))
			goto exit_remove;
		if (data->have_temp_offset & (1 << i)) {
			err = device_create_file(dev,
						 &sda_temp_offset[i].dev_attr);
			if (err)
				goto exit_remove;
		}
	}

	err = device_create_file(dev, &sda_caseopen[0].dev_attr);
	if (err)
		goto exit_remove;

	if (sio_data->kind == nct6776) {
		err = device_create_file(dev, &sda_caseopen[1].dev_attr);
		if (err)
			goto exit_remove;
	}

	err = device_create_file(dev, &dev_attr_name);
	if (err)
		goto exit_remove;

	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	w83627ehf_device_remove_files(dev);
exit_release:
	release_region(res->start, IOREGION_LENGTH);
exit:
	return err;
}