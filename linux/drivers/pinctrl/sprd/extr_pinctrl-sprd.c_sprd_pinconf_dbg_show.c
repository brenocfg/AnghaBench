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
struct seq_file {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long) ; 
 int sprd_pinconf_get_config (struct pinctrl_dev*,unsigned int,unsigned long*) ; 

__attribute__((used)) static void sprd_pinconf_dbg_show(struct pinctrl_dev *pctldev,
				  struct seq_file *s, unsigned int pin_id)
{
	unsigned long config;
	int ret;

	ret = sprd_pinconf_get_config(pctldev, pin_id, &config);
	if (ret)
		return;

	seq_printf(s, "0x%lx", config);
}