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
struct stmfx_pinctrl {int /*<<< orphan*/  gpio_chip; } ;
struct seq_file {int dummy; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct stmfx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin_nolock (struct pinctrl_dev*,unsigned int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int stmfx_gpio_get (int /*<<< orphan*/ *,unsigned int) ; 
 int stmfx_gpio_get_direction (int /*<<< orphan*/ *,unsigned int) ; 
 int stmfx_pinconf_get_pupd (struct stmfx_pinctrl*,unsigned int) ; 
 int stmfx_pinconf_get_type (struct stmfx_pinctrl*,unsigned int) ; 

__attribute__((used)) static void stmfx_pinconf_dbg_show(struct pinctrl_dev *pctldev,
				   struct seq_file *s, unsigned int offset)
{
	struct stmfx_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct pinctrl_gpio_range *range;
	int dir, type, pupd, val;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, offset);
	if (!range)
		return;

	dir = stmfx_gpio_get_direction(&pctl->gpio_chip, offset);
	if (dir < 0)
		return;
	type = stmfx_pinconf_get_type(pctl, offset);
	if (type < 0)
		return;
	pupd = stmfx_pinconf_get_pupd(pctl, offset);
	if (pupd < 0)
		return;
	val = stmfx_gpio_get(&pctl->gpio_chip, offset);
	if (val < 0)
		return;

	if (!dir) {
		seq_printf(s, "output %s ", val ? "high" : "low");
		if (type)
			seq_printf(s, "open drain %s internal pull-up ",
				   pupd ? "with" : "without");
		else
			seq_puts(s, "push pull no pull ");
	} else {
		seq_printf(s, "input %s ", val ? "high" : "low");
		if (type)
			seq_printf(s, "with internal pull-%s ",
				   pupd ? "up" : "down");
		else
			seq_printf(s, "%s ", pupd ? "floating" : "analog");
	}
}