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
typedef  void* u32 ;
struct sti_pwm_compat_data {struct reg_field* reg_fields; void* cpt_num_devs; void* pwm_num_devs; } ;
struct sti_pwm_chip {void* pwm_cpt_int_stat; int /*<<< orphan*/  regmap; void* pwm_cpt_int_en; void* pwm_cpt_en; void* pwm_out_en; void* prescale_high; void* prescale_low; struct sti_pwm_compat_data* cdata; struct device* dev; } ;
struct reg_field {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ PTR_ERR_OR_ZERO (void*) ; 
 size_t PWMCLK_PRESCALE_HIGH ; 
 size_t PWMCLK_PRESCALE_LOW ; 
 size_t PWM_CPT_EN ; 
 size_t PWM_CPT_INT_EN ; 
 size_t PWM_CPT_INT_STAT ; 
 size_t PWM_OUT_EN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_regmap_field_alloc (struct device*,int /*<<< orphan*/ ,struct reg_field const) ; 
 int of_property_read_u32 (struct device_node*,char*,void**) ; 

__attribute__((used)) static int sti_pwm_probe_dt(struct sti_pwm_chip *pc)
{
	struct device *dev = pc->dev;
	const struct reg_field *reg_fields;
	struct device_node *np = dev->of_node;
	struct sti_pwm_compat_data *cdata = pc->cdata;
	u32 num_devs;
	int ret;

	ret = of_property_read_u32(np, "st,pwm-num-chan", &num_devs);
	if (!ret)
		cdata->pwm_num_devs = num_devs;

	ret = of_property_read_u32(np, "st,capture-num-chan", &num_devs);
	if (!ret)
		cdata->cpt_num_devs = num_devs;

	if (!cdata->pwm_num_devs && !cdata->cpt_num_devs) {
		dev_err(dev, "No channels configured\n");
		return -EINVAL;
	}

	reg_fields = cdata->reg_fields;

	pc->prescale_low = devm_regmap_field_alloc(dev, pc->regmap,
					reg_fields[PWMCLK_PRESCALE_LOW]);
	if (IS_ERR(pc->prescale_low))
		return PTR_ERR(pc->prescale_low);

	pc->prescale_high = devm_regmap_field_alloc(dev, pc->regmap,
					reg_fields[PWMCLK_PRESCALE_HIGH]);
	if (IS_ERR(pc->prescale_high))
		return PTR_ERR(pc->prescale_high);


	pc->pwm_out_en = devm_regmap_field_alloc(dev, pc->regmap,
						 reg_fields[PWM_OUT_EN]);
	if (IS_ERR(pc->pwm_out_en))
		return PTR_ERR(pc->pwm_out_en);

	pc->pwm_cpt_en = devm_regmap_field_alloc(dev, pc->regmap,
						 reg_fields[PWM_CPT_EN]);
	if (IS_ERR(pc->pwm_cpt_en))
		return PTR_ERR(pc->pwm_cpt_en);

	pc->pwm_cpt_int_en = devm_regmap_field_alloc(dev, pc->regmap,
						reg_fields[PWM_CPT_INT_EN]);
	if (IS_ERR(pc->pwm_cpt_int_en))
		return PTR_ERR(pc->pwm_cpt_int_en);

	pc->pwm_cpt_int_stat = devm_regmap_field_alloc(dev, pc->regmap,
						reg_fields[PWM_CPT_INT_STAT]);
	if (PTR_ERR_OR_ZERO(pc->pwm_cpt_int_stat))
		return PTR_ERR(pc->pwm_cpt_int_stat);

	return 0;
}