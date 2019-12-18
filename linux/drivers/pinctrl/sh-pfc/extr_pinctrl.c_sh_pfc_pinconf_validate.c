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
struct sh_pfc_pin {int configs; } ;
struct sh_pfc {TYPE_1__* info; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {struct sh_pfc_pin* pins; } ;

/* Variables and functions */
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_PULL_DOWN 131 
#define  PIN_CONFIG_BIAS_PULL_UP 130 
#define  PIN_CONFIG_DRIVE_STRENGTH 129 
#define  PIN_CONFIG_POWER_SOURCE 128 
 int SH_PFC_PIN_CFG_DRIVE_STRENGTH ; 
 int SH_PFC_PIN_CFG_IO_VOLTAGE ; 
 int SH_PFC_PIN_CFG_PULL_DOWN ; 
 int SH_PFC_PIN_CFG_PULL_UP ; 
 int SH_PFC_PIN_CFG_PULL_UP_DOWN ; 
 int sh_pfc_get_pin_index (struct sh_pfc*,unsigned int) ; 

__attribute__((used)) static bool sh_pfc_pinconf_validate(struct sh_pfc *pfc, unsigned int _pin,
				    enum pin_config_param param)
{
	int idx = sh_pfc_get_pin_index(pfc, _pin);
	const struct sh_pfc_pin *pin = &pfc->info->pins[idx];

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		return pin->configs & SH_PFC_PIN_CFG_PULL_UP_DOWN;

	case PIN_CONFIG_BIAS_PULL_UP:
		return pin->configs & SH_PFC_PIN_CFG_PULL_UP;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		return pin->configs & SH_PFC_PIN_CFG_PULL_DOWN;

	case PIN_CONFIG_DRIVE_STRENGTH:
		return pin->configs & SH_PFC_PIN_CFG_DRIVE_STRENGTH;

	case PIN_CONFIG_POWER_SOURCE:
		return pin->configs & SH_PFC_PIN_CFG_IO_VOLTAGE;

	default:
		return false;
	}
}