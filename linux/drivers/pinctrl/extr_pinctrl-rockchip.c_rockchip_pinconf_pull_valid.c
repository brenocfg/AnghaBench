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
struct rockchip_pin_ctrl {int type; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int PIN_CONFIG_BIAS_DISABLE ; 
 int PIN_CONFIG_BIAS_PULL_PIN_DEFAULT ; 
#define  PX30 136 
#define  RK2928 135 
#define  RK3066B 134 
#define  RK3128 133 
#define  RK3188 132 
#define  RK3288 131 
#define  RK3368 130 
#define  RK3399 129 
#define  RV1108 128 

__attribute__((used)) static bool rockchip_pinconf_pull_valid(struct rockchip_pin_ctrl *ctrl,
					enum pin_config_param pull)
{
	switch (ctrl->type) {
	case RK2928:
	case RK3128:
		return (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT ||
					pull == PIN_CONFIG_BIAS_DISABLE);
	case RK3066B:
		return pull ? false : true;
	case PX30:
	case RV1108:
	case RK3188:
	case RK3288:
	case RK3368:
	case RK3399:
		return (pull != PIN_CONFIG_BIAS_PULL_PIN_DEFAULT);
	}

	return false;
}