#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct pmic_gpio_state {int dummy; } ;
struct pmic_gpio_pad {int out_value; int function; char const* const power_source; size_t pullup; size_t buffer_type; size_t strength; char const* const atest; char const* const dtest_buffer; scalar_t__ output_enabled; scalar_t__ analog_pass; int /*<<< orphan*/  lv_mv_type; scalar_t__ input_enabled; } ;
struct pinctrl_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {struct pmic_gpio_pad* drv_data; } ;

/* Variables and functions */
 int PMIC_GPIO_FUNC_INDEX_DTEST1 ; 
 int PMIC_GPIO_FUNC_INDEX_FUNC3 ; 
 char const* const PMIC_GPIO_PHYSICAL_OFFSET ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_EN_CTL ; 
 int PMIC_GPIO_REG_MASTER_EN_SHIFT ; 
 int /*<<< orphan*/  PMIC_MPP_REG_RT_STS ; 
 int PMIC_MPP_REG_RT_STS_VAL_MASK ; 
 struct pmic_gpio_state* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 char const* const* pmic_gpio_functions ; 
 int pmic_gpio_read (struct pmic_gpio_state*,struct pmic_gpio_pad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const* const) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void pmic_gpio_config_dbg_show(struct pinctrl_dev *pctldev,
				      struct seq_file *s, unsigned pin)
{
	struct pmic_gpio_state *state = pinctrl_dev_get_drvdata(pctldev);
	struct pmic_gpio_pad *pad;
	int ret, val, function;

	static const char *const biases[] = {
		"pull-up 30uA", "pull-up 1.5uA", "pull-up 31.5uA",
		"pull-up 1.5uA + 30uA boost", "pull-down 10uA", "no pull"
	};
	static const char *const buffer_types[] = {
		"push-pull", "open-drain", "open-source"
	};
	static const char *const strengths[] = {
		"no", "high", "medium", "low"
	};

	pad = pctldev->desc->pins[pin].drv_data;

	seq_printf(s, " gpio%-2d:", pin + PMIC_GPIO_PHYSICAL_OFFSET);

	val = pmic_gpio_read(state, pad, PMIC_GPIO_REG_EN_CTL);

	if (val < 0 || !(val >> PMIC_GPIO_REG_MASTER_EN_SHIFT)) {
		seq_puts(s, " ---");
	} else {
		if (pad->input_enabled) {
			ret = pmic_gpio_read(state, pad, PMIC_MPP_REG_RT_STS);
			if (ret < 0)
				return;

			ret &= PMIC_MPP_REG_RT_STS_VAL_MASK;
			pad->out_value = ret;
		}
		/*
		 * For the non-LV/MV subtypes only 2 special functions are
		 * available, offsetting the dtest function values by 2.
		 */
		function = pad->function;
		if (!pad->lv_mv_type &&
				pad->function >= PMIC_GPIO_FUNC_INDEX_FUNC3)
			function += PMIC_GPIO_FUNC_INDEX_DTEST1 -
				PMIC_GPIO_FUNC_INDEX_FUNC3;

		if (pad->analog_pass)
			seq_puts(s, " analog-pass");
		else
			seq_printf(s, " %-4s",
					pad->output_enabled ? "out" : "in");
		seq_printf(s, " %-4s", pad->out_value ? "high" : "low");
		seq_printf(s, " %-7s", pmic_gpio_functions[function]);
		seq_printf(s, " vin-%d", pad->power_source);
		seq_printf(s, " %-27s", biases[pad->pullup]);
		seq_printf(s, " %-10s", buffer_types[pad->buffer_type]);
		seq_printf(s, " %-7s", strengths[pad->strength]);
		seq_printf(s, " atest-%d", pad->atest);
		seq_printf(s, " dtest-%d", pad->dtest_buffer);
	}
}