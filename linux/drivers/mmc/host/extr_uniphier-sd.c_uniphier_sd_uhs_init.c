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
struct uniphier_sd_priv {void* pinstate_uhs; void* pinctrl; void* pinstate_default; } ;
struct TYPE_2__ {int /*<<< orphan*/  start_signal_voltage_switch; } ;
struct tmio_mmc_host {TYPE_1__ ops; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 char* PINCTRL_STATE_DEFAULT ; 
 int PTR_ERR (void*) ; 
 void* devm_pinctrl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 void* pinctrl_lookup_state (void*,char*) ; 
 int /*<<< orphan*/  uniphier_sd_start_signal_voltage_switch ; 

__attribute__((used)) static int uniphier_sd_uhs_init(struct tmio_mmc_host *host,
				struct uniphier_sd_priv *priv)
{
	priv->pinctrl = devm_pinctrl_get(mmc_dev(host->mmc));
	if (IS_ERR(priv->pinctrl))
		return PTR_ERR(priv->pinctrl);

	priv->pinstate_default = pinctrl_lookup_state(priv->pinctrl,
						      PINCTRL_STATE_DEFAULT);
	if (IS_ERR(priv->pinstate_default))
		return PTR_ERR(priv->pinstate_default);

	priv->pinstate_uhs = pinctrl_lookup_state(priv->pinctrl, "uhs");
	if (IS_ERR(priv->pinstate_uhs))
		return PTR_ERR(priv->pinstate_uhs);

	host->ops.start_signal_voltage_switch =
					uniphier_sd_start_signal_voltage_switch;

	return 0;
}