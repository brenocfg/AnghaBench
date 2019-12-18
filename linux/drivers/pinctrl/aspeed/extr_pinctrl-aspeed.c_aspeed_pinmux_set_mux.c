#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct aspeed_sig_expr {int dummy; } ;
struct TYPE_5__ {struct aspeed_pin_function* functions; struct aspeed_pin_group* groups; } ;
struct aspeed_pinctrl_data {TYPE_2__ pinmux; TYPE_1__* pins; } ;
struct aspeed_pin_group {int npins; int* pins; } ;
struct aspeed_pin_function {int /*<<< orphan*/  name; } ;
struct aspeed_pin_desc {int /*<<< orphan*/  name; struct aspeed_sig_expr*** prios; } ;
struct TYPE_4__ {struct aspeed_pin_desc* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int aspeed_disable_sig (TYPE_2__*,struct aspeed_sig_expr const**) ; 
 struct aspeed_sig_expr* aspeed_find_expr_by_name (struct aspeed_sig_expr const**,int /*<<< orphan*/ ) ; 
 int aspeed_sig_expr_enable (TYPE_2__*,struct aspeed_sig_expr const*) ; 
 char* get_defined_functions (struct aspeed_pin_desc const*) ; 
 char* get_defined_signals (struct aspeed_pin_desc const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct aspeed_pinctrl_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 

int aspeed_pinmux_set_mux(struct pinctrl_dev *pctldev, unsigned int function,
			  unsigned int group)
{
	int i;
	int ret;
	struct aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);
	const struct aspeed_pin_group *pgroup = &pdata->pinmux.groups[group];
	const struct aspeed_pin_function *pfunc =
		&pdata->pinmux.functions[function];

	for (i = 0; i < pgroup->npins; i++) {
		int pin = pgroup->pins[i];
		const struct aspeed_pin_desc *pdesc = pdata->pins[pin].drv_data;
		const struct aspeed_sig_expr *expr = NULL;
		const struct aspeed_sig_expr **funcs;
		const struct aspeed_sig_expr ***prios;

		pr_debug("Muxing pin %d for %s\n", pin, pfunc->name);

		if (!pdesc)
			return -EINVAL;

		prios = pdesc->prios;

		if (!prios)
			continue;

		/* Disable functions at a higher priority than that requested */
		while ((funcs = *prios)) {
			expr = aspeed_find_expr_by_name(funcs, pfunc->name);

			if (expr)
				break;

			ret = aspeed_disable_sig(&pdata->pinmux, funcs);
			if (ret)
				return ret;

			prios++;
		}

		if (!expr) {
			char *functions = get_defined_functions(pdesc);
			char *signals = get_defined_signals(pdesc);

			pr_warn("No function %s found on pin %s (%d). Found signal(s) %s for function(s) %s\n",
				pfunc->name, pdesc->name, pin, signals,
				functions);
			kfree(signals);
			kfree(functions);

			return -ENXIO;
		}

		ret = aspeed_sig_expr_enable(&pdata->pinmux, expr);
		if (ret)
			return ret;
	}

	return 0;
}