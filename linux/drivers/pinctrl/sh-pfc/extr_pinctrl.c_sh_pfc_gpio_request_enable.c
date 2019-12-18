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
struct sh_pfc_pinctrl {struct sh_pfc_pin_config* configs; struct sh_pfc* pfc; } ;
struct sh_pfc_pin_config {int gpio_enabled; } ;
struct sh_pfc_pin {int /*<<< orphan*/  enum_id; } ;
struct sh_pfc {int /*<<< orphan*/  lock; TYPE_1__* info; int /*<<< orphan*/  gpio; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {struct sh_pfc_pin* pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  PINMUX_TYPE_GPIO ; 
 struct sh_pfc_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int sh_pfc_config_mux (struct sh_pfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sh_pfc_get_pin_index (struct sh_pfc*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh_pfc_gpio_request_enable(struct pinctrl_dev *pctldev,
				      struct pinctrl_gpio_range *range,
				      unsigned offset)
{
	struct sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	struct sh_pfc *pfc = pmx->pfc;
	int idx = sh_pfc_get_pin_index(pfc, offset);
	struct sh_pfc_pin_config *cfg = &pmx->configs[idx];
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&pfc->lock, flags);

	if (!pfc->gpio) {
		/* If GPIOs are handled externally the pin mux type need to be
		 * set to GPIO here.
		 */
		const struct sh_pfc_pin *pin = &pfc->info->pins[idx];

		ret = sh_pfc_config_mux(pfc, pin->enum_id, PINMUX_TYPE_GPIO);
		if (ret < 0)
			goto done;
	}

	cfg->gpio_enabled = true;

	ret = 0;

done:
	spin_unlock_irqrestore(&pfc->lock, flags);

	return ret;
}