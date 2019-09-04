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
typedef  scalar_t__ u16 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct nct6775_sio_data {size_t kind; int /*<<< orphan*/  sioreg; } ;
struct nct6775_data {size_t kind; int bank; int in_num; int pwm_num; int auto_pwm_num; int temp_fixed_num; int num_temp_alarms; int num_temp_beeps; int temp_mask; int virt_temp_mask; int has_fan_div; int target_temp_mask; int tolerance_mask; int speed_tolerance_limit; int have_in; int have_temp; int have_temp_fixed; scalar_t__** reg_temp; scalar_t__* reg_temp_config; int* temp_src; int have_vid; int has_fan; struct attribute_group** groups; int /*<<< orphan*/  name; int /*<<< orphan*/  vrm; void* vid; int /*<<< orphan*/ * REG_TEMP_SEL; int /*<<< orphan*/ * REG_TEMP_SOURCE; int /*<<< orphan*/ * REG_WEIGHT_TEMP_SEL; void* REG_BEEP; void* REG_ALARM; void** REG_WEIGHT_TEMP; void* REG_TEMP_OFFSET; void* REG_CRITICAL_PWM; void* CRITICAL_PWM_ENABLE_MASK; void* REG_CRITICAL_PWM_ENABLE; void* REG_CRITICAL_TEMP_TOLERANCE; void* REG_CRITICAL_TEMP; void* REG_AUTO_PWM; void* REG_AUTO_TEMP; void* PWM_MODE_MASK; void* REG_PWM_MODE; void* REG_PWM_READ; void** REG_PWM; void* REG_TOLERANCE_H; void** REG_FAN_TIME; void* FAN_PULSE_SHIFT; void* REG_FAN_PULSES; void* REG_FAN_MIN; void* REG_FAN_MODE; void* REG_FAN; void* REG_TARGET; void** REG_IN_MINMAX; void* REG_VIN; void* DIODE_MASK; void* REG_DIODE; void* REG_VBAT; void* REG_CONFIG; void* temp_label; void* fan_from_reg_min; void* fan_from_reg; void* BEEP_BITS; int /*<<< orphan*/  ALARM_BITS; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  addr; int /*<<< orphan*/  sioreg; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  DRVNAME ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOREGION_LENGTH ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (struct attribute_group*) ; 
 int /*<<< orphan*/  NCT6106_ALARM_BITS ; 
 void* NCT6106_BEEP_BITS ; 
 void* NCT6106_CRITICAL_PWM_ENABLE_MASK ; 
 void* NCT6106_DIODE_MASK ; 
 void* NCT6106_FAN_PULSE_SHIFT ; 
 void* NCT6106_PWM_MODE_MASK ; 
 void* NCT6106_REG_ALARM ; 
 void* NCT6106_REG_AUTO_PWM ; 
 void* NCT6106_REG_AUTO_TEMP ; 
 void* NCT6106_REG_BEEP ; 
 void* NCT6106_REG_CRITICAL_PWM ; 
 void* NCT6106_REG_CRITICAL_PWM_ENABLE ; 
 void* NCT6106_REG_CRITICAL_TEMP ; 
 void* NCT6106_REG_CRITICAL_TEMP_TOLERANCE ; 
 void* NCT6106_REG_DIODE ; 
 void* NCT6106_REG_FAN ; 
 void* NCT6106_REG_FAN_MIN ; 
 void* NCT6106_REG_FAN_MODE ; 
 void* NCT6106_REG_FAN_PULSES ; 
 void* NCT6106_REG_FAN_START_OUTPUT ; 
 void* NCT6106_REG_FAN_STEP_DOWN_TIME ; 
 void* NCT6106_REG_FAN_STEP_UP_TIME ; 
 void* NCT6106_REG_FAN_STOP_OUTPUT ; 
 void* NCT6106_REG_FAN_STOP_TIME ; 
 void* NCT6106_REG_IN ; 
 void* NCT6106_REG_IN_MAX ; 
 void* NCT6106_REG_IN_MIN ; 
 void* NCT6106_REG_PWM ; 
 void* NCT6106_REG_PWM_MODE ; 
 void* NCT6106_REG_PWM_READ ; 
 void* NCT6106_REG_TARGET ; 
 scalar_t__* NCT6106_REG_TEMP ; 
 scalar_t__* NCT6106_REG_TEMP_ALTERNATE ; 
 scalar_t__* NCT6106_REG_TEMP_CONFIG ; 
 scalar_t__* NCT6106_REG_TEMP_CRIT ; 
 scalar_t__* NCT6106_REG_TEMP_CRIT_H ; 
 scalar_t__* NCT6106_REG_TEMP_CRIT_L ; 
 scalar_t__* NCT6106_REG_TEMP_HYST ; 
 scalar_t__* NCT6106_REG_TEMP_MON ; 
 void* NCT6106_REG_TEMP_OFFSET ; 
 scalar_t__* NCT6106_REG_TEMP_OVER ; 
 int /*<<< orphan*/ * NCT6106_REG_TEMP_SEL ; 
 int /*<<< orphan*/ * NCT6106_REG_TEMP_SOURCE ; 
 void* NCT6106_REG_VBAT ; 
 void* NCT6106_REG_WEIGHT_DUTY_BASE ; 
 void* NCT6106_REG_WEIGHT_DUTY_STEP ; 
 void* NCT6106_REG_WEIGHT_TEMP_BASE ; 
 int /*<<< orphan*/ * NCT6106_REG_WEIGHT_TEMP_SEL ; 
 void* NCT6106_REG_WEIGHT_TEMP_STEP ; 
 void* NCT6106_REG_WEIGHT_TEMP_STEP_TOL ; 
 int /*<<< orphan*/  NCT6775_ALARM_BITS ; 
 void* NCT6775_BEEP_BITS ; 
 void* NCT6775_DIODE_MASK ; 
 void* NCT6775_FAN_PULSE_SHIFT ; 
 int /*<<< orphan*/  NCT6775_LD_HWM ; 
 int /*<<< orphan*/  NCT6775_LD_VID ; 
 void* NCT6775_PWM_MODE_MASK ; 
 void* NCT6775_REG_ALARM ; 
 void* NCT6775_REG_AUTO_PWM ; 
 void* NCT6775_REG_AUTO_TEMP ; 
 void* NCT6775_REG_BEEP ; 
 void* NCT6775_REG_CONFIG ; 
 void* NCT6775_REG_CRITICAL_TEMP ; 
 void* NCT6775_REG_CRITICAL_TEMP_TOLERANCE ; 
 int NCT6775_REG_CR_FAN_DEBOUNCE ; 
 void* NCT6775_REG_DIODE ; 
 void* NCT6775_REG_FAN ; 
 void* NCT6775_REG_FAN_MAX_OUTPUT ; 
 void* NCT6775_REG_FAN_MIN ; 
 void* NCT6775_REG_FAN_MODE ; 
 void* NCT6775_REG_FAN_PULSES ; 
 void* NCT6775_REG_FAN_START_OUTPUT ; 
 void* NCT6775_REG_FAN_STEP_DOWN_TIME ; 
 void* NCT6775_REG_FAN_STEP_OUTPUT ; 
 void* NCT6775_REG_FAN_STEP_UP_TIME ; 
 void* NCT6775_REG_FAN_STOP_OUTPUT ; 
 void* NCT6775_REG_FAN_STOP_TIME ; 
 void* NCT6775_REG_IN ; 
 void* NCT6775_REG_IN_MAX ; 
 void* NCT6775_REG_IN_MIN ; 
 void* NCT6775_REG_PWM ; 
 void* NCT6775_REG_PWM_MODE ; 
 void* NCT6775_REG_PWM_READ ; 
 void* NCT6775_REG_TARGET ; 
 scalar_t__* NCT6775_REG_TEMP ; 
 scalar_t__* NCT6775_REG_TEMP_ALTERNATE ; 
 scalar_t__* NCT6775_REG_TEMP_CONFIG ; 
 scalar_t__* NCT6775_REG_TEMP_CRIT ; 
 scalar_t__* NCT6775_REG_TEMP_HYST ; 
 scalar_t__* NCT6775_REG_TEMP_MON ; 
 void* NCT6775_REG_TEMP_OFFSET ; 
 scalar_t__* NCT6775_REG_TEMP_OVER ; 
 void* NCT6775_REG_TEMP_SEL ; 
 void* NCT6775_REG_TEMP_SOURCE ; 
 void* NCT6775_REG_VBAT ; 
 void* NCT6775_REG_WEIGHT_DUTY_STEP ; 
 void* NCT6775_REG_WEIGHT_TEMP_BASE ; 
 void* NCT6775_REG_WEIGHT_TEMP_SEL ; 
 void* NCT6775_REG_WEIGHT_TEMP_STEP ; 
 void* NCT6775_REG_WEIGHT_TEMP_STEP_TOL ; 
 int NCT6775_TEMP_MASK ; 
 int NCT6775_VIRT_TEMP_MASK ; 
 int /*<<< orphan*/  NCT6776_ALARM_BITS ; 
 void* NCT6776_BEEP_BITS ; 
 void* NCT6776_PWM_MODE_MASK ; 
 void* NCT6776_REG_BEEP ; 
 void* NCT6776_REG_FAN_MIN ; 
 void* NCT6776_REG_FAN_PULSES ; 
 void* NCT6776_REG_FAN_STEP_DOWN_TIME ; 
 void* NCT6776_REG_FAN_STEP_UP_TIME ; 
 void* NCT6776_REG_PWM_MODE ; 
 scalar_t__* NCT6776_REG_TEMP_ALTERNATE ; 
 scalar_t__* NCT6776_REG_TEMP_CONFIG ; 
 scalar_t__* NCT6776_REG_TEMP_CRIT ; 
 void* NCT6776_REG_TOLERANCE_H ; 
 void* NCT6776_REG_WEIGHT_DUTY_BASE ; 
 void* NCT6776_TEMP_MASK ; 
 void* NCT6776_VIRT_TEMP_MASK ; 
 int /*<<< orphan*/  NCT6779_ALARM_BITS ; 
 void* NCT6779_BEEP_BITS ; 
 void* NCT6779_CRITICAL_PWM_ENABLE_MASK ; 
 void* NCT6779_REG_ALARM ; 
 void* NCT6779_REG_CRITICAL_PWM ; 
 void* NCT6779_REG_CRITICAL_PWM_ENABLE ; 
 void* NCT6779_REG_FAN ; 
 void* NCT6779_REG_FAN_PULSES ; 
 void* NCT6779_REG_IN ; 
 scalar_t__* NCT6779_REG_TEMP ; 
 scalar_t__* NCT6779_REG_TEMP_ALTERNATE ; 
 scalar_t__* NCT6779_REG_TEMP_CONFIG ; 
 scalar_t__* NCT6779_REG_TEMP_CRIT ; 
 scalar_t__* NCT6779_REG_TEMP_HYST ; 
 scalar_t__* NCT6779_REG_TEMP_MON ; 
 void* NCT6779_REG_TEMP_OFFSET ; 
 scalar_t__* NCT6779_REG_TEMP_OVER ; 
 int NCT6779_TEMP_MASK ; 
 int NCT6779_VIRT_TEMP_MASK ; 
 int /*<<< orphan*/  NCT6791_ALARM_BITS ; 
 void* NCT6791_REG_ALARM ; 
 void* NCT6791_REG_WEIGHT_DUTY_BASE ; 
 void* NCT6791_REG_WEIGHT_DUTY_STEP ; 
 void* NCT6791_REG_WEIGHT_TEMP_BASE ; 
 int /*<<< orphan*/ * NCT6791_REG_WEIGHT_TEMP_SEL ; 
 void* NCT6791_REG_WEIGHT_TEMP_STEP ; 
 void* NCT6791_REG_WEIGHT_TEMP_STEP_TOL ; 
 int NCT6791_TEMP_MASK ; 
 int NCT6791_VIRT_TEMP_MASK ; 
 void* NCT6792_REG_BEEP ; 
 scalar_t__* NCT6792_REG_TEMP_MON ; 
 int NCT6792_TEMP_MASK ; 
 int NCT6792_VIRT_TEMP_MASK ; 
 int NCT6793_TEMP_MASK ; 
 int NCT6793_VIRT_TEMP_MASK ; 
 int NCT6795_TEMP_MASK ; 
 int NCT6795_VIRT_TEMP_MASK ; 
 int NCT6796_TEMP_MASK ; 
 int NCT6796_VIRT_TEMP_MASK ; 
 int NUM_TEMP ; 
 int NUM_TEMP_FIXED ; 
 int PTR_ERR (struct attribute_group*) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  add_temp_sensors (struct nct6775_data*,int /*<<< orphan*/ *,int*,int*) ; 
 struct nct6775_sio_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,...) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct nct6775_data*,struct attribute_group**) ; 
 struct nct6775_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fan_debounce ; 
 void* fan_from_reg13 ; 
 void* fan_from_reg16 ; 
 void* fan_from_reg8 ; 
 void* fan_from_reg_rpm ; 
 int fls (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
#define  nct6106 136 
#define  nct6775 135 
 int /*<<< orphan*/  nct6775_check_fan_inputs (struct nct6775_data*) ; 
 struct attribute_group* nct6775_create_attr_group (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nct6775_device_names ; 
 int /*<<< orphan*/  nct6775_fan_template_group ; 
 struct attribute_group nct6775_group_other ; 
 int /*<<< orphan*/  nct6775_in_template_group ; 
 int /*<<< orphan*/  nct6775_init_device (struct nct6775_data*) ; 
 int /*<<< orphan*/  nct6775_init_fan_common (struct device*,struct nct6775_data*) ; 
 int /*<<< orphan*/  nct6775_pwm_template_group ; 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
 void* nct6775_temp_label ; 
 int /*<<< orphan*/  nct6775_temp_template_group ; 
#define  nct6776 134 
 void* nct6776_temp_label ; 
#define  nct6779 133 
 void* nct6779_temp_label ; 
#define  nct6791 132 
#define  nct6792 131 
 void* nct6792_temp_label ; 
#define  nct6793 130 
 void* nct6793_temp_label ; 
#define  nct6795 129 
 void* nct6795_temp_label ; 
#define  nct6796 128 
 void* nct6796_temp_label ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nct6775_data*) ; 
 int superio_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_exit (int /*<<< orphan*/ ) ; 
 void* superio_inb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  superio_outb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static int nct6775_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct nct6775_sio_data *sio_data = dev_get_platdata(dev);
	struct nct6775_data *data;
	struct resource *res;
	int i, s, err = 0;
	int src, mask, available;
	const u16 *reg_temp, *reg_temp_over, *reg_temp_hyst, *reg_temp_config;
	const u16 *reg_temp_mon, *reg_temp_alternate, *reg_temp_crit;
	const u16 *reg_temp_crit_l = NULL, *reg_temp_crit_h = NULL;
	int num_reg_temp, num_reg_temp_mon;
	u8 cr2a;
	struct attribute_group *group;
	struct device *hwmon_dev;
	int num_attr_groups = 0;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!devm_request_region(&pdev->dev, res->start, IOREGION_LENGTH,
				 DRVNAME))
		return -EBUSY;

	data = devm_kzalloc(&pdev->dev, sizeof(struct nct6775_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->kind = sio_data->kind;
	data->sioreg = sio_data->sioreg;
	data->addr = res->start;
	mutex_init(&data->update_lock);
	data->name = nct6775_device_names[data->kind];
	data->bank = 0xff;		/* Force initial bank selection */
	platform_set_drvdata(pdev, data);

	switch (data->kind) {
	case nct6106:
		data->in_num = 9;
		data->pwm_num = 3;
		data->auto_pwm_num = 4;
		data->temp_fixed_num = 3;
		data->num_temp_alarms = 6;
		data->num_temp_beeps = 6;

		data->fan_from_reg = fan_from_reg13;
		data->fan_from_reg_min = fan_from_reg13;

		data->temp_label = nct6776_temp_label;
		data->temp_mask = NCT6776_TEMP_MASK;
		data->virt_temp_mask = NCT6776_VIRT_TEMP_MASK;

		data->REG_VBAT = NCT6106_REG_VBAT;
		data->REG_DIODE = NCT6106_REG_DIODE;
		data->DIODE_MASK = NCT6106_DIODE_MASK;
		data->REG_VIN = NCT6106_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6106_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6106_REG_IN_MAX;
		data->REG_TARGET = NCT6106_REG_TARGET;
		data->REG_FAN = NCT6106_REG_FAN;
		data->REG_FAN_MODE = NCT6106_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6106_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6106_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6106_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6106_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6106_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6106_REG_FAN_STEP_DOWN_TIME;
		data->REG_PWM[0] = NCT6106_REG_PWM;
		data->REG_PWM[1] = NCT6106_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6106_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6106_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6106_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6106_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6106_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6106_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6106_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6106_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6106_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6106_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_CRITICAL_PWM_ENABLE = NCT6106_REG_CRITICAL_PWM_ENABLE;
		data->CRITICAL_PWM_ENABLE_MASK
		  = NCT6106_CRITICAL_PWM_ENABLE_MASK;
		data->REG_CRITICAL_PWM = NCT6106_REG_CRITICAL_PWM;
		data->REG_TEMP_OFFSET = NCT6106_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6106_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6106_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6106_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6106_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6106_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6106_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6106_REG_ALARM;
		data->ALARM_BITS = NCT6106_ALARM_BITS;
		data->REG_BEEP = NCT6106_REG_BEEP;
		data->BEEP_BITS = NCT6106_BEEP_BITS;

		reg_temp = NCT6106_REG_TEMP;
		reg_temp_mon = NCT6106_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6106_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6106_REG_TEMP_MON);
		reg_temp_over = NCT6106_REG_TEMP_OVER;
		reg_temp_hyst = NCT6106_REG_TEMP_HYST;
		reg_temp_config = NCT6106_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6106_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6106_REG_TEMP_CRIT;
		reg_temp_crit_l = NCT6106_REG_TEMP_CRIT_L;
		reg_temp_crit_h = NCT6106_REG_TEMP_CRIT_H;

		break;
	case nct6775:
		data->in_num = 9;
		data->pwm_num = 3;
		data->auto_pwm_num = 6;
		data->has_fan_div = true;
		data->temp_fixed_num = 3;
		data->num_temp_alarms = 3;
		data->num_temp_beeps = 3;

		data->ALARM_BITS = NCT6775_ALARM_BITS;
		data->BEEP_BITS = NCT6775_BEEP_BITS;

		data->fan_from_reg = fan_from_reg16;
		data->fan_from_reg_min = fan_from_reg8;
		data->target_temp_mask = 0x7f;
		data->tolerance_mask = 0x0f;
		data->speed_tolerance_limit = 15;

		data->temp_label = nct6775_temp_label;
		data->temp_mask = NCT6775_TEMP_MASK;
		data->virt_temp_mask = NCT6775_VIRT_TEMP_MASK;

		data->REG_CONFIG = NCT6775_REG_CONFIG;
		data->REG_VBAT = NCT6775_REG_VBAT;
		data->REG_DIODE = NCT6775_REG_DIODE;
		data->DIODE_MASK = NCT6775_DIODE_MASK;
		data->REG_VIN = NCT6775_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6775_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6775_REG_IN_MAX;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6775_REG_FAN;
		data->REG_FAN_MODE = NCT6775_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6775_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6775_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6775_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6775_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6775_REG_FAN_STEP_DOWN_TIME;
		data->REG_PWM[0] = NCT6775_REG_PWM;
		data->REG_PWM[1] = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[3] = NCT6775_REG_FAN_MAX_OUTPUT;
		data->REG_PWM[4] = NCT6775_REG_FAN_STEP_OUTPUT;
		data->REG_PWM[5] = NCT6775_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM_READ = NCT6775_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6775_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6775_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6775_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6775_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6775_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6775_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_TEMP_OFFSET = NCT6775_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6775_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6775_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6775_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6775_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6775_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6775_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6775_REG_ALARM;
		data->REG_BEEP = NCT6775_REG_BEEP;

		reg_temp = NCT6775_REG_TEMP;
		reg_temp_mon = NCT6775_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6775_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6775_REG_TEMP_MON);
		reg_temp_over = NCT6775_REG_TEMP_OVER;
		reg_temp_hyst = NCT6775_REG_TEMP_HYST;
		reg_temp_config = NCT6775_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6775_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6775_REG_TEMP_CRIT;

		break;
	case nct6776:
		data->in_num = 9;
		data->pwm_num = 3;
		data->auto_pwm_num = 4;
		data->has_fan_div = false;
		data->temp_fixed_num = 3;
		data->num_temp_alarms = 3;
		data->num_temp_beeps = 6;

		data->ALARM_BITS = NCT6776_ALARM_BITS;
		data->BEEP_BITS = NCT6776_BEEP_BITS;

		data->fan_from_reg = fan_from_reg13;
		data->fan_from_reg_min = fan_from_reg13;
		data->target_temp_mask = 0xff;
		data->tolerance_mask = 0x07;
		data->speed_tolerance_limit = 63;

		data->temp_label = nct6776_temp_label;
		data->temp_mask = NCT6776_TEMP_MASK;
		data->virt_temp_mask = NCT6776_VIRT_TEMP_MASK;

		data->REG_CONFIG = NCT6775_REG_CONFIG;
		data->REG_VBAT = NCT6775_REG_VBAT;
		data->REG_DIODE = NCT6775_REG_DIODE;
		data->DIODE_MASK = NCT6775_DIODE_MASK;
		data->REG_VIN = NCT6775_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6775_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6775_REG_IN_MAX;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6775_REG_FAN;
		data->REG_FAN_MODE = NCT6775_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6776_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6776_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6775_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6776_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6776_REG_FAN_STEP_DOWN_TIME;
		data->REG_TOLERANCE_H = NCT6776_REG_TOLERANCE_H;
		data->REG_PWM[0] = NCT6775_REG_PWM;
		data->REG_PWM[1] = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6775_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6776_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6775_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6776_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6776_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6775_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6775_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6775_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6775_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_TEMP_OFFSET = NCT6775_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6775_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6775_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6775_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6775_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6775_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6775_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6775_REG_ALARM;
		data->REG_BEEP = NCT6776_REG_BEEP;

		reg_temp = NCT6775_REG_TEMP;
		reg_temp_mon = NCT6775_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6775_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6775_REG_TEMP_MON);
		reg_temp_over = NCT6775_REG_TEMP_OVER;
		reg_temp_hyst = NCT6775_REG_TEMP_HYST;
		reg_temp_config = NCT6776_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6776_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6776_REG_TEMP_CRIT;

		break;
	case nct6779:
		data->in_num = 15;
		data->pwm_num = 5;
		data->auto_pwm_num = 4;
		data->has_fan_div = false;
		data->temp_fixed_num = 6;
		data->num_temp_alarms = 2;
		data->num_temp_beeps = 2;

		data->ALARM_BITS = NCT6779_ALARM_BITS;
		data->BEEP_BITS = NCT6779_BEEP_BITS;

		data->fan_from_reg = fan_from_reg_rpm;
		data->fan_from_reg_min = fan_from_reg13;
		data->target_temp_mask = 0xff;
		data->tolerance_mask = 0x07;
		data->speed_tolerance_limit = 63;

		data->temp_label = nct6779_temp_label;
		data->temp_mask = NCT6779_TEMP_MASK;
		data->virt_temp_mask = NCT6779_VIRT_TEMP_MASK;

		data->REG_CONFIG = NCT6775_REG_CONFIG;
		data->REG_VBAT = NCT6775_REG_VBAT;
		data->REG_DIODE = NCT6775_REG_DIODE;
		data->DIODE_MASK = NCT6775_DIODE_MASK;
		data->REG_VIN = NCT6779_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6775_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6775_REG_IN_MAX;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6779_REG_FAN;
		data->REG_FAN_MODE = NCT6775_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6776_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6779_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6775_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6776_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6776_REG_FAN_STEP_DOWN_TIME;
		data->REG_TOLERANCE_H = NCT6776_REG_TOLERANCE_H;
		data->REG_PWM[0] = NCT6775_REG_PWM;
		data->REG_PWM[1] = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6775_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6776_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6775_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6776_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6776_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6775_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6775_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6775_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6775_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_CRITICAL_PWM_ENABLE = NCT6779_REG_CRITICAL_PWM_ENABLE;
		data->CRITICAL_PWM_ENABLE_MASK
		  = NCT6779_CRITICAL_PWM_ENABLE_MASK;
		data->REG_CRITICAL_PWM = NCT6779_REG_CRITICAL_PWM;
		data->REG_TEMP_OFFSET = NCT6779_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6775_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6775_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6775_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6775_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6775_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6775_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6779_REG_ALARM;
		data->REG_BEEP = NCT6776_REG_BEEP;

		reg_temp = NCT6779_REG_TEMP;
		reg_temp_mon = NCT6779_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6779_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6779_REG_TEMP_MON);
		reg_temp_over = NCT6779_REG_TEMP_OVER;
		reg_temp_hyst = NCT6779_REG_TEMP_HYST;
		reg_temp_config = NCT6779_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6779_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6779_REG_TEMP_CRIT;

		break;
	case nct6791:
	case nct6792:
	case nct6793:
	case nct6795:
	case nct6796:
		data->in_num = 15;
		data->pwm_num = (data->kind == nct6796) ? 7 : 6;
		data->auto_pwm_num = 4;
		data->has_fan_div = false;
		data->temp_fixed_num = 6;
		data->num_temp_alarms = 2;
		data->num_temp_beeps = 2;

		data->ALARM_BITS = NCT6791_ALARM_BITS;
		data->BEEP_BITS = NCT6779_BEEP_BITS;

		data->fan_from_reg = fan_from_reg_rpm;
		data->fan_from_reg_min = fan_from_reg13;
		data->target_temp_mask = 0xff;
		data->tolerance_mask = 0x07;
		data->speed_tolerance_limit = 63;

		switch (data->kind) {
		default:
		case nct6791:
			data->temp_label = nct6779_temp_label;
			data->temp_mask = NCT6791_TEMP_MASK;
			data->virt_temp_mask = NCT6791_VIRT_TEMP_MASK;
			break;
		case nct6792:
			data->temp_label = nct6792_temp_label;
			data->temp_mask = NCT6792_TEMP_MASK;
			data->virt_temp_mask = NCT6792_VIRT_TEMP_MASK;
			break;
		case nct6793:
			data->temp_label = nct6793_temp_label;
			data->temp_mask = NCT6793_TEMP_MASK;
			data->virt_temp_mask = NCT6793_VIRT_TEMP_MASK;
			break;
		case nct6795:
			data->temp_label = nct6795_temp_label;
			data->temp_mask = NCT6795_TEMP_MASK;
			data->virt_temp_mask = NCT6795_VIRT_TEMP_MASK;
			break;
		case nct6796:
			data->temp_label = nct6796_temp_label;
			data->temp_mask = NCT6796_TEMP_MASK;
			data->virt_temp_mask = NCT6796_VIRT_TEMP_MASK;
			break;
		}

		data->REG_CONFIG = NCT6775_REG_CONFIG;
		data->REG_VBAT = NCT6775_REG_VBAT;
		data->REG_DIODE = NCT6775_REG_DIODE;
		data->DIODE_MASK = NCT6775_DIODE_MASK;
		data->REG_VIN = NCT6779_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6775_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6775_REG_IN_MAX;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6779_REG_FAN;
		data->REG_FAN_MODE = NCT6775_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6776_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6779_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6775_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6776_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6776_REG_FAN_STEP_DOWN_TIME;
		data->REG_TOLERANCE_H = NCT6776_REG_TOLERANCE_H;
		data->REG_PWM[0] = NCT6775_REG_PWM;
		data->REG_PWM[1] = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6791_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6791_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6775_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6776_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6776_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6775_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6775_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6775_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6775_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_CRITICAL_PWM_ENABLE = NCT6779_REG_CRITICAL_PWM_ENABLE;
		data->CRITICAL_PWM_ENABLE_MASK
		  = NCT6779_CRITICAL_PWM_ENABLE_MASK;
		data->REG_CRITICAL_PWM = NCT6779_REG_CRITICAL_PWM;
		data->REG_TEMP_OFFSET = NCT6779_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6775_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6775_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6791_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6791_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6791_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6791_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6791_REG_ALARM;
		if (data->kind == nct6791)
			data->REG_BEEP = NCT6776_REG_BEEP;
		else
			data->REG_BEEP = NCT6792_REG_BEEP;

		reg_temp = NCT6779_REG_TEMP;
		num_reg_temp = ARRAY_SIZE(NCT6779_REG_TEMP);
		if (data->kind == nct6791) {
			reg_temp_mon = NCT6779_REG_TEMP_MON;
			num_reg_temp_mon = ARRAY_SIZE(NCT6779_REG_TEMP_MON);
		} else {
			reg_temp_mon = NCT6792_REG_TEMP_MON;
			num_reg_temp_mon = ARRAY_SIZE(NCT6792_REG_TEMP_MON);
		}
		reg_temp_over = NCT6779_REG_TEMP_OVER;
		reg_temp_hyst = NCT6779_REG_TEMP_HYST;
		reg_temp_config = NCT6779_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6779_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6779_REG_TEMP_CRIT;

		break;
	default:
		return -ENODEV;
	}
	data->have_in = BIT(data->in_num) - 1;
	data->have_temp = 0;

	/*
	 * On some boards, not all available temperature sources are monitored,
	 * even though some of the monitoring registers are unused.
	 * Get list of unused monitoring registers, then detect if any fan
	 * controls are configured to use unmonitored temperature sources.
	 * If so, assign the unmonitored temperature sources to available
	 * monitoring registers.
	 */
	mask = 0;
	available = 0;
	for (i = 0; i < num_reg_temp; i++) {
		if (reg_temp[i] == 0)
			continue;

		src = nct6775_read_value(data, data->REG_TEMP_SOURCE[i]) & 0x1f;
		if (!src || (mask & BIT(src)))
			available |= BIT(i);

		mask |= BIT(src);
	}

	/*
	 * Now find unmonitored temperature registers and enable monitoring
	 * if additional monitoring registers are available.
	 */
	add_temp_sensors(data, data->REG_TEMP_SEL, &available, &mask);
	add_temp_sensors(data, data->REG_WEIGHT_TEMP_SEL, &available, &mask);

	mask = 0;
	s = NUM_TEMP_FIXED;	/* First dynamic temperature attribute */
	for (i = 0; i < num_reg_temp; i++) {
		if (reg_temp[i] == 0)
			continue;

		src = nct6775_read_value(data, data->REG_TEMP_SOURCE[i]) & 0x1f;
		if (!src || (mask & BIT(src)))
			continue;

		if (!(data->temp_mask & BIT(src))) {
			dev_info(dev,
				 "Invalid temperature source %d at index %d, source register 0x%x, temp register 0x%x\n",
				 src, i, data->REG_TEMP_SOURCE[i], reg_temp[i]);
			continue;
		}

		mask |= BIT(src);

		/* Use fixed index for SYSTIN(1), CPUTIN(2), AUXTIN(3) */
		if (src <= data->temp_fixed_num) {
			data->have_temp |= BIT(src - 1);
			data->have_temp_fixed |= BIT(src - 1);
			data->reg_temp[0][src - 1] = reg_temp[i];
			data->reg_temp[1][src - 1] = reg_temp_over[i];
			data->reg_temp[2][src - 1] = reg_temp_hyst[i];
			if (reg_temp_crit_h && reg_temp_crit_h[i])
				data->reg_temp[3][src - 1] = reg_temp_crit_h[i];
			else if (reg_temp_crit[src - 1])
				data->reg_temp[3][src - 1]
				  = reg_temp_crit[src - 1];
			if (reg_temp_crit_l && reg_temp_crit_l[i])
				data->reg_temp[4][src - 1] = reg_temp_crit_l[i];
			data->reg_temp_config[src - 1] = reg_temp_config[i];
			data->temp_src[src - 1] = src;
			continue;
		}

		if (s >= NUM_TEMP)
			continue;

		/* Use dynamic index for other sources */
		data->have_temp |= BIT(s);
		data->reg_temp[0][s] = reg_temp[i];
		data->reg_temp[1][s] = reg_temp_over[i];
		data->reg_temp[2][s] = reg_temp_hyst[i];
		data->reg_temp_config[s] = reg_temp_config[i];
		if (reg_temp_crit_h && reg_temp_crit_h[i])
			data->reg_temp[3][s] = reg_temp_crit_h[i];
		else if (reg_temp_crit[src - 1])
			data->reg_temp[3][s] = reg_temp_crit[src - 1];
		if (reg_temp_crit_l && reg_temp_crit_l[i])
			data->reg_temp[4][s] = reg_temp_crit_l[i];

		data->temp_src[s] = src;
		s++;
	}

	/*
	 * Repeat with temperatures used for fan control.
	 * This set of registers does not support limits.
	 */
	for (i = 0; i < num_reg_temp_mon; i++) {
		if (reg_temp_mon[i] == 0)
			continue;

		src = nct6775_read_value(data, data->REG_TEMP_SEL[i]) & 0x1f;
		if (!src)
			continue;

		if (!(data->temp_mask & BIT(src))) {
			dev_info(dev,
				 "Invalid temperature source %d at index %d, source register 0x%x, temp register 0x%x\n",
				 src, i, data->REG_TEMP_SEL[i],
				 reg_temp_mon[i]);
			continue;
		}

		/*
		 * For virtual temperature sources, the 'virtual' temperature
		 * for each fan reflects a different temperature, and there
		 * are no duplicates.
		 */
		if (!(data->virt_temp_mask & BIT(src))) {
			if (mask & BIT(src))
				continue;
			mask |= BIT(src);
		}

		/* Use fixed index for SYSTIN(1), CPUTIN(2), AUXTIN(3) */
		if (src <= data->temp_fixed_num) {
			if (data->have_temp & BIT(src - 1))
				continue;
			data->have_temp |= BIT(src - 1);
			data->have_temp_fixed |= BIT(src - 1);
			data->reg_temp[0][src - 1] = reg_temp_mon[i];
			data->temp_src[src - 1] = src;
			continue;
		}

		if (s >= NUM_TEMP)
			continue;

		/* Use dynamic index for other sources */
		data->have_temp |= BIT(s);
		data->reg_temp[0][s] = reg_temp_mon[i];
		data->temp_src[s] = src;
		s++;
	}

#ifdef USE_ALTERNATE
	/*
	 * Go through the list of alternate temp registers and enable
	 * if possible.
	 * The temperature is already monitored if the respective bit in <mask>
	 * is set.
	 */
	for (i = 0; i < 31; i++) {
		if (!(data->temp_mask & BIT(i + 1)))
			continue;
		if (!reg_temp_alternate[i])
			continue;
		if (mask & BIT(i + 1))
			continue;
		if (i < data->temp_fixed_num) {
			if (data->have_temp & BIT(i))
				continue;
			data->have_temp |= BIT(i);
			data->have_temp_fixed |= BIT(i);
			data->reg_temp[0][i] = reg_temp_alternate[i];
			if (i < num_reg_temp) {
				data->reg_temp[1][i] = reg_temp_over[i];
				data->reg_temp[2][i] = reg_temp_hyst[i];
			}
			data->temp_src[i] = i + 1;
			continue;
		}

		if (s >= NUM_TEMP)	/* Abort if no more space */
			break;

		data->have_temp |= BIT(s);
		data->reg_temp[0][s] = reg_temp_alternate[i];
		data->temp_src[s] = i + 1;
		s++;
	}
#endif /* USE_ALTERNATE */

	/* Initialize the chip */
	nct6775_init_device(data);

	err = superio_enter(sio_data->sioreg);
	if (err)
		return err;

	cr2a = superio_inb(sio_data->sioreg, 0x2a);
	switch (data->kind) {
	case nct6775:
		data->have_vid = (cr2a & 0x40);
		break;
	case nct6776:
		data->have_vid = (cr2a & 0x60) == 0x40;
		break;
	case nct6106:
	case nct6779:
	case nct6791:
	case nct6792:
	case nct6793:
	case nct6795:
	case nct6796:
		break;
	}

	/*
	 * Read VID value
	 * We can get the VID input values directly at logical device D 0xe3.
	 */
	if (data->have_vid) {
		superio_select(sio_data->sioreg, NCT6775_LD_VID);
		data->vid = superio_inb(sio_data->sioreg, 0xe3);
		data->vrm = vid_which_vrm();
	}

	if (fan_debounce) {
		u8 tmp;

		superio_select(sio_data->sioreg, NCT6775_LD_HWM);
		tmp = superio_inb(sio_data->sioreg,
				  NCT6775_REG_CR_FAN_DEBOUNCE);
		switch (data->kind) {
		case nct6106:
			tmp |= 0xe0;
			break;
		case nct6775:
			tmp |= 0x1e;
			break;
		case nct6776:
		case nct6779:
			tmp |= 0x3e;
			break;
		case nct6791:
		case nct6792:
		case nct6793:
		case nct6795:
		case nct6796:
			tmp |= 0x7e;
			break;
		}
		superio_outb(sio_data->sioreg, NCT6775_REG_CR_FAN_DEBOUNCE,
			     tmp);
		dev_info(&pdev->dev, "Enabled fan debounce for chip %s\n",
			 data->name);
	}

	nct6775_check_fan_inputs(data);

	superio_exit(sio_data->sioreg);

	/* Read fan clock dividers immediately */
	nct6775_init_fan_common(dev, data);

	/* Register sysfs hooks */
	group = nct6775_create_attr_group(dev, &nct6775_pwm_template_group,
					  data->pwm_num);
	if (IS_ERR(group))
		return PTR_ERR(group);

	data->groups[num_attr_groups++] = group;

	group = nct6775_create_attr_group(dev, &nct6775_in_template_group,
					  fls(data->have_in));
	if (IS_ERR(group))
		return PTR_ERR(group);

	data->groups[num_attr_groups++] = group;

	group = nct6775_create_attr_group(dev, &nct6775_fan_template_group,
					  fls(data->has_fan));
	if (IS_ERR(group))
		return PTR_ERR(group);

	data->groups[num_attr_groups++] = group;

	group = nct6775_create_attr_group(dev, &nct6775_temp_template_group,
					  fls(data->have_temp));
	if (IS_ERR(group))
		return PTR_ERR(group);

	data->groups[num_attr_groups++] = group;
	data->groups[num_attr_groups++] = &nct6775_group_other;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, data->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}