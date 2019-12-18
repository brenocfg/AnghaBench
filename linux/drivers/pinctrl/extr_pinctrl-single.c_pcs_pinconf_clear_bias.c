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
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcs_bias ; 
 int /*<<< orphan*/  pcs_pinconf_set (struct pinctrl_dev*,unsigned int,unsigned long*,int) ; 
 unsigned long pinconf_to_config_packed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcs_pinconf_clear_bias(struct pinctrl_dev *pctldev, unsigned pin)
{
	unsigned long config;
	int i;
	for (i = 0; i < ARRAY_SIZE(pcs_bias); i++) {
		config = pinconf_to_config_packed(pcs_bias[i], 0);
		pcs_pinconf_set(pctldev, pin, &config, 1);
	}
}