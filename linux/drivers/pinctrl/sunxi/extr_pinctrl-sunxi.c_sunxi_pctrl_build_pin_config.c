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
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PIN_CONFIG_BIAS_DISABLE ; 
 int PIN_CONFIG_DRIVE_STRENGTH ; 
 unsigned long* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 scalar_t__ sunxi_pctrl_has_bias_prop (struct device_node*) ; 
 scalar_t__ sunxi_pctrl_has_drive_prop (struct device_node*) ; 
 int sunxi_pctrl_parse_bias_prop (struct device_node*) ; 
 int sunxi_pctrl_parse_drive_prop (struct device_node*) ; 

__attribute__((used)) static unsigned long *sunxi_pctrl_build_pin_config(struct device_node *node,
						   unsigned int *len)
{
	unsigned long *pinconfig;
	unsigned int configlen = 0, idx = 0;
	int ret;

	if (sunxi_pctrl_has_drive_prop(node))
		configlen++;
	if (sunxi_pctrl_has_bias_prop(node))
		configlen++;

	/*
	 * If we don't have any configuration, bail out
	 */
	if (!configlen)
		return NULL;

	pinconfig = kcalloc(configlen, sizeof(*pinconfig), GFP_KERNEL);
	if (!pinconfig)
		return ERR_PTR(-ENOMEM);

	if (sunxi_pctrl_has_drive_prop(node)) {
		int drive = sunxi_pctrl_parse_drive_prop(node);
		if (drive < 0) {
			ret = drive;
			goto err_free;
		}

		pinconfig[idx++] = pinconf_to_config_packed(PIN_CONFIG_DRIVE_STRENGTH,
							  drive);
	}

	if (sunxi_pctrl_has_bias_prop(node)) {
		int pull = sunxi_pctrl_parse_bias_prop(node);
		int arg = 0;
		if (pull < 0) {
			ret = pull;
			goto err_free;
		}

		if (pull != PIN_CONFIG_BIAS_DISABLE)
			arg = 1; /* hardware uses weak pull resistors */

		pinconfig[idx++] = pinconf_to_config_packed(pull, arg);
	}


	*len = configlen;
	return pinconfig;

err_free:
	kfree(pinconfig);
	return ERR_PTR(ret);
}