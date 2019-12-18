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
typedef  int u32 ;
struct mrfld_pinctrl {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BUFCFG_OD_EN ; 
 int BUFCFG_PD_EN ; 
 int BUFCFG_PUPD_VAL_20K ; 
 int BUFCFG_PUPD_VAL_2K ; 
 int BUFCFG_PUPD_VAL_50K ; 
 int BUFCFG_PUPD_VAL_MASK ; 
 int BUFCFG_PUPD_VAL_SHIFT ; 
 int BUFCFG_PU_EN ; 
 int BUFCFG_Px_EN_MASK ; 
 int BUFCFG_SLEWSEL ; 
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_PULL_DOWN 131 
#define  PIN_CONFIG_BIAS_PULL_UP 130 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  mrfld_update_bufcfg (struct mrfld_pinctrl*,unsigned int,int,int) ; 
 unsigned int pinconf_to_config_argument (unsigned long) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mrfld_config_set_pin(struct mrfld_pinctrl *mp, unsigned int pin,
				unsigned long config)
{
	unsigned int param = pinconf_to_config_param(config);
	unsigned int arg = pinconf_to_config_argument(config);
	u32 bits = 0, mask = 0;
	unsigned long flags;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		mask |= BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAL_MASK;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		mask |= BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAL_MASK;
		bits |= BUFCFG_PU_EN;

		switch (arg) {
		case 50000:
			bits |= BUFCFG_PUPD_VAL_50K << BUFCFG_PUPD_VAL_SHIFT;
			break;
		case 20000:
			bits |= BUFCFG_PUPD_VAL_20K << BUFCFG_PUPD_VAL_SHIFT;
			break;
		case 2000:
			bits |= BUFCFG_PUPD_VAL_2K << BUFCFG_PUPD_VAL_SHIFT;
			break;
		default:
			return -EINVAL;
		}

		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		mask |= BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAL_MASK;
		bits |= BUFCFG_PD_EN;

		switch (arg) {
		case 50000:
			bits |= BUFCFG_PUPD_VAL_50K << BUFCFG_PUPD_VAL_SHIFT;
			break;
		case 20000:
			bits |= BUFCFG_PUPD_VAL_20K << BUFCFG_PUPD_VAL_SHIFT;
			break;
		case 2000:
			bits |= BUFCFG_PUPD_VAL_2K << BUFCFG_PUPD_VAL_SHIFT;
			break;
		default:
			return -EINVAL;
		}

		break;

	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		mask |= BUFCFG_OD_EN;
		if (arg)
			bits |= BUFCFG_OD_EN;
		break;

	case PIN_CONFIG_SLEW_RATE:
		mask |= BUFCFG_SLEWSEL;
		if (arg)
			bits |= BUFCFG_SLEWSEL;
		break;
	}

	raw_spin_lock_irqsave(&mp->lock, flags);
	mrfld_update_bufcfg(mp, pin, bits, mask);
	raw_spin_unlock_irqrestore(&mp->lock, flags);

	return 0;
}