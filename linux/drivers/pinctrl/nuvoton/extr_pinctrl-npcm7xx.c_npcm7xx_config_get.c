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
typedef  unsigned long u32 ;
struct pinctrl_dev {int dummy; } ;
struct npcm7xx_pinctrl {int /*<<< orphan*/  gcr_regmap; struct npcm7xx_gpio* gpio_bank; } ;
struct TYPE_2__ {unsigned int ngpio; } ;
struct npcm7xx_gpio {scalar_t__ base; TYPE_1__ gc; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 unsigned int NPCM7XX_GPIO_PER_BANK ; 
 scalar_t__ NPCM7XX_GP_N_DBNC ; 
 scalar_t__ NPCM7XX_GP_N_IEM ; 
 scalar_t__ NPCM7XX_GP_N_OE ; 
 scalar_t__ NPCM7XX_GP_N_OTYP ; 
 scalar_t__ NPCM7XX_GP_N_PD ; 
 scalar_t__ NPCM7XX_GP_N_PU ; 
#define  PIN_CONFIG_BIAS_DISABLE 137 
#define  PIN_CONFIG_BIAS_PULL_DOWN 136 
#define  PIN_CONFIG_BIAS_PULL_UP 135 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 134 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 133 
#define  PIN_CONFIG_DRIVE_STRENGTH 132 
#define  PIN_CONFIG_INPUT_DEBOUNCE 131 
#define  PIN_CONFIG_INPUT_ENABLE 130 
#define  PIN_CONFIG_OUTPUT 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 unsigned long ioread32 (scalar_t__) ; 
 int npcm7xx_get_drive_strength (struct pinctrl_dev*,unsigned int) ; 
 int npcm7xx_get_slew_rate (struct npcm7xx_gpio*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct npcm7xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int npcm7xx_config_get(struct pinctrl_dev *pctldev, unsigned int pin,
			      unsigned long *config)
{
	enum pin_config_param param = pinconf_to_config_param(*config);
	struct npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);
	struct npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PER_BANK];
	int gpio = (pin % bank->gc.ngpio);
	unsigned long pinmask = BIT(gpio);
	u32 ie, oe, pu, pd;
	int rc = 0;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
		pu = ioread32(bank->base + NPCM7XX_GP_N_PU) & pinmask;
		pd = ioread32(bank->base + NPCM7XX_GP_N_PD) & pinmask;
		if (param == PIN_CONFIG_BIAS_DISABLE)
			rc = (!pu && !pd);
		else if (param == PIN_CONFIG_BIAS_PULL_UP)
			rc = (pu && !pd);
		else if (param == PIN_CONFIG_BIAS_PULL_DOWN)
			rc = (!pu && pd);
		break;
	case PIN_CONFIG_OUTPUT:
	case PIN_CONFIG_INPUT_ENABLE:
		ie = ioread32(bank->base + NPCM7XX_GP_N_IEM) & pinmask;
		oe = ioread32(bank->base + NPCM7XX_GP_N_OE) & pinmask;
		if (param == PIN_CONFIG_INPUT_ENABLE)
			rc = (ie && !oe);
		else if (param == PIN_CONFIG_OUTPUT)
			rc = (!ie && oe);
		break;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		rc = !(ioread32(bank->base + NPCM7XX_GP_N_OTYP) & pinmask);
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		rc = ioread32(bank->base + NPCM7XX_GP_N_OTYP) & pinmask;
		break;
	case PIN_CONFIG_INPUT_DEBOUNCE:
		rc = ioread32(bank->base + NPCM7XX_GP_N_DBNC) & pinmask;
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		rc = npcm7xx_get_drive_strength(pctldev, pin);
		if (rc)
			*config = pinconf_to_config_packed(param, rc);
		break;
	case PIN_CONFIG_SLEW_RATE:
		rc = npcm7xx_get_slew_rate(bank, npcm->gcr_regmap, pin);
		if (rc >= 0)
			*config = pinconf_to_config_packed(param, rc);
		break;
	default:
		return -ENOTSUPP;
	}

	if (!rc)
		return -EINVAL;

	return 0;
}