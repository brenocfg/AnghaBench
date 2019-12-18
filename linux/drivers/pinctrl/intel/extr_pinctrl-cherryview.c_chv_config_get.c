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
typedef  int u16 ;
struct pinctrl_dev {int dummy; } ;
struct chv_pinctrl {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int /*<<< orphan*/  CHV_PADCTRL0 ; 
 int CHV_PADCTRL0_GPIOCFG_HIZ ; 
 int CHV_PADCTRL0_GPIOCFG_MASK ; 
 int CHV_PADCTRL0_GPIOCFG_SHIFT ; 
#define  CHV_PADCTRL0_TERM_1K 135 
#define  CHV_PADCTRL0_TERM_20K 134 
#define  CHV_PADCTRL0_TERM_5K 133 
 int CHV_PADCTRL0_TERM_MASK ; 
 int CHV_PADCTRL0_TERM_SHIFT ; 
 int CHV_PADCTRL0_TERM_UP ; 
 int /*<<< orphan*/  CHV_PADCTRL1 ; 
 int CHV_PADCTRL1_ODEN ; 
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 128 
 int /*<<< orphan*/  chv_lock ; 
 int /*<<< orphan*/  chv_padreg (struct chv_pinctrl*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct chv_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chv_config_get(struct pinctrl_dev *pctldev, unsigned int pin,
			  unsigned long *config)
{
	struct chv_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	unsigned long flags;
	u32 ctrl0, ctrl1;
	u16 arg = 0;
	u32 term;

	raw_spin_lock_irqsave(&chv_lock, flags);
	ctrl0 = readl(chv_padreg(pctrl, pin, CHV_PADCTRL0));
	ctrl1 = readl(chv_padreg(pctrl, pin, CHV_PADCTRL1));
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	term = (ctrl0 & CHV_PADCTRL0_TERM_MASK) >> CHV_PADCTRL0_TERM_SHIFT;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (term)
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		if (!(ctrl0 & CHV_PADCTRL0_TERM_UP))
			return -EINVAL;

		switch (term) {
		case CHV_PADCTRL0_TERM_20K:
			arg = 20000;
			break;
		case CHV_PADCTRL0_TERM_5K:
			arg = 5000;
			break;
		case CHV_PADCTRL0_TERM_1K:
			arg = 1000;
			break;
		}

		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (!term || (ctrl0 & CHV_PADCTRL0_TERM_UP))
			return -EINVAL;

		switch (term) {
		case CHV_PADCTRL0_TERM_20K:
			arg = 20000;
			break;
		case CHV_PADCTRL0_TERM_5K:
			arg = 5000;
			break;
		}

		break;

	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		if (!(ctrl1 & CHV_PADCTRL1_ODEN))
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE: {
		u32 cfg;

		cfg = ctrl0 & CHV_PADCTRL0_GPIOCFG_MASK;
		cfg >>= CHV_PADCTRL0_GPIOCFG_SHIFT;
		if (cfg != CHV_PADCTRL0_GPIOCFG_HIZ)
			return -EINVAL;

		break;
	}

	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);
	return 0;
}