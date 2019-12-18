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
struct sh_pfc_pinctrl {struct sh_pfc* pfc; } ;
struct sh_pfc_pin {int configs; int /*<<< orphan*/  enum_id; } ;
struct sh_pfc {int /*<<< orphan*/  lock; TYPE_1__* info; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {struct sh_pfc_pin* pins; } ;

/* Variables and functions */
 int EINVAL ; 
 int PINMUX_TYPE_INPUT ; 
 int PINMUX_TYPE_OUTPUT ; 
 unsigned int SH_PFC_PIN_CFG_INPUT ; 
 unsigned int SH_PFC_PIN_CFG_OUTPUT ; 
 struct sh_pfc_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int sh_pfc_config_mux (struct sh_pfc*,int /*<<< orphan*/ ,int) ; 
 int sh_pfc_get_pin_index (struct sh_pfc*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh_pfc_gpio_set_direction(struct pinctrl_dev *pctldev,
				     struct pinctrl_gpio_range *range,
				     unsigned offset, bool input)
{
	struct sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	struct sh_pfc *pfc = pmx->pfc;
	int new_type = input ? PINMUX_TYPE_INPUT : PINMUX_TYPE_OUTPUT;
	int idx = sh_pfc_get_pin_index(pfc, offset);
	const struct sh_pfc_pin *pin = &pfc->info->pins[idx];
	unsigned long flags;
	unsigned int dir;
	int ret;

	/* Check if the requested direction is supported by the pin. Not all SoC
	 * provide pin config data, so perform the check conditionally.
	 */
	if (pin->configs) {
		dir = input ? SH_PFC_PIN_CFG_INPUT : SH_PFC_PIN_CFG_OUTPUT;
		if (!(pin->configs & dir))
			return -EINVAL;
	}

	spin_lock_irqsave(&pfc->lock, flags);

	ret = sh_pfc_config_mux(pfc, pin->enum_id, new_type);
	if (ret < 0)
		goto done;

done:
	spin_unlock_irqrestore(&pfc->lock, flags);
	return ret;
}