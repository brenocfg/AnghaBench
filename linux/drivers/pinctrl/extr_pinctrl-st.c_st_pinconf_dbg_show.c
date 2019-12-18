#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_pio_control {int dummy; } ;
struct seq_file {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_PINCONF_UNPACK_OD (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_PU (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_RT (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_RT_CLK (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_RT_CLKNOTDATA (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_RT_DELAY (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_RT_DOUBLE_EDGE (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_RT_INVERTCLK (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* pc_to_bank (struct st_pio_control*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 struct st_pio_control* st_get_pio_control (struct pinctrl_dev*,unsigned int) ; 
 int /*<<< orphan*/  st_gpio_get_direction (int /*<<< orphan*/ *,int) ; 
 int st_gpio_pin (unsigned int) ; 
 unsigned int st_pctl_get_pin_function (struct st_pio_control*,int) ; 
 int /*<<< orphan*/  st_pinconf_get (struct pinctrl_dev*,unsigned int,unsigned long*) ; 

__attribute__((used)) static void st_pinconf_dbg_show(struct pinctrl_dev *pctldev,
				   struct seq_file *s, unsigned pin_id)
{
	struct st_pio_control *pc;
	unsigned long config;
	unsigned int function;
	int offset = st_gpio_pin(pin_id);
	char f[16];

	mutex_unlock(&pctldev->mutex);
	pc = st_get_pio_control(pctldev, pin_id);
	st_pinconf_get(pctldev, pin_id, &config);
	mutex_lock(&pctldev->mutex);

	function = st_pctl_get_pin_function(pc, offset);
	if (function)
		snprintf(f, 10, "Alt Fn %u", function);
	else
		snprintf(f, 5, "GPIO");

	seq_printf(s, "[OE:%d,PU:%ld,OD:%ld]\t%s\n"
		"\t\t[retime:%ld,invclk:%ld,clknotdat:%ld,"
		"de:%ld,rt-clk:%ld,rt-delay:%ld]",
		!st_gpio_get_direction(&pc_to_bank(pc)->gpio_chip, offset),
		ST_PINCONF_UNPACK_PU(config),
		ST_PINCONF_UNPACK_OD(config),
		f,
		ST_PINCONF_UNPACK_RT(config),
		ST_PINCONF_UNPACK_RT_INVERTCLK(config),
		ST_PINCONF_UNPACK_RT_CLKNOTDATA(config),
		ST_PINCONF_UNPACK_RT_DOUBLE_EDGE(config),
		ST_PINCONF_UNPACK_RT_CLK(config),
		ST_PINCONF_UNPACK_RT_DELAY(config));
}