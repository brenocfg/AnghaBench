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
struct mcp23s08 {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  MCP_GPPU ; 
#define  PIN_CONFIG_BIAS_PULL_UP 128 
 int mcp_read (struct mcp23s08*,int /*<<< orphan*/ ,unsigned int*) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct mcp23s08* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mcp_pinconf_get(struct pinctrl_dev *pctldev, unsigned int pin,
			      unsigned long *config)
{
	struct mcp23s08 *mcp = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	unsigned int data, status;
	int ret;

	switch (param) {
	case PIN_CONFIG_BIAS_PULL_UP:
		ret = mcp_read(mcp, MCP_GPPU, &data);
		if (ret < 0)
			return ret;
		status = (data & BIT(pin)) ? 1 : 0;
		break;
	default:
		return -ENOTSUPP;
	}

	*config = 0;

	return status ? 0 : -EINVAL;
}